//
// code .asoundrc
// echo "defaults.pcm.card 2" > ~/.asoundrc
// echo "defaults.ctl.card 2" >> ~/.asoundrc
/*

sudo apt-get install libasound2-dev


sudo nano /boot/config.txt
sudo nano /boot/firmware/config.txt
dtparam=audio=off
dtoverlay=i2s-mmap
dtoverlay=wm8960-soundcard

git clone https://github.com/waveshare/WM8960-Audio-HAT
cd WM8960-Audio-HAT/
sudo ./install.sh
cd ..

gcc -o audio_test audio_test.c -lasound -lm

libcamera-jpeg -o test.jpg
libcamera-vid -t 10000 -o test.h264

*/
#include <alsa/asoundlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M_PI 3.14159265358979323846 /* pi */

// 톤 생성 함수 (스테레오)
void generate_tone(short *buffer, int sample_rate, int frequency, int duration)
{
    int samples = sample_rate * duration;
    for (int i = 0; i < samples; i++)
    {
        short value = (short)(32767 * 0.5 * sin(2 * M_PI * frequency * i / sample_rate));
        buffer[2 * i] = value;     // 좌측 채널
        buffer[2 * i + 1] = value; // 우측 채널
    }
}
// WAV 파일 읽기 함수 (모노 및 스테레오 지원)
int read_wav_file(const char *filename, short **buffer, int *sample_rate, int *total_samples, int *channels_out)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("WAV 파일 열기 실패: %s\n", filename);
        return -1;
    }

    char header[44];
    fread(header, 1, 44, file);
    *sample_rate = *(int *)(header + 24);
    *channels_out = *(short *)(header + 22);
    int data_size = *(int *)(header + 40);
    *total_samples = data_size / (*channels_out * sizeof(short));

    short *raw_buffer = malloc(data_size);
    if (!raw_buffer)
    {
        printf("메모리 할당 실패\n");
        fclose(file);
        return -1;
    }
    fread(raw_buffer, 1, data_size, file);
    fclose(file);

    // 스테레오로 변환 (모노라면 복제)
    *buffer = malloc(*total_samples * 2 * sizeof(short));
    if (*channels_out == 1)
    {
        for (int i = 0; i < *total_samples; i++)
        {
            (*buffer)[2 * i] = raw_buffer[i];     // 좌측 채널
            (*buffer)[2 * i + 1] = raw_buffer[i]; // 우측 채널
        }
    }
    else if (*channels_out == 2)
    {
        memcpy(*buffer, raw_buffer, data_size);
    }
    else
    {
        printf("지원되지 않는 채널 수: %d\n", *channels_out);
        free(raw_buffer);
        free(*buffer);
        return -1;
    }

    free(raw_buffer);
    return 0;
}

// 지원 파라미터 출력 함수
void print_hw_params(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
    unsigned int rate_min, rate_max;
    int channels_min, channels_max;
    snd_pcm_uframes_t period_min, period_max;

    snd_pcm_hw_params_get_rate_min(params, &rate_min, 0);
    snd_pcm_hw_params_get_rate_max(params, &rate_max, 0);
    snd_pcm_hw_params_get_channels_min(params, &channels_min);
    snd_pcm_hw_params_get_channels_max(params, &channels_max);
    snd_pcm_hw_params_get_period_size_min(params, &period_min, 0);
    snd_pcm_hw_params_get_period_size_max(params, &period_max, 0);

    printf("지원 샘플레이트: %u - %u Hz\n", rate_min, rate_max);
    printf("지원 채널: %d - %d\n", channels_min, channels_max);
    printf("지원 프레임 크기: %lu - %lu\n", period_min, period_max);
}
// 스피커 재생 함수
int play_audio(const char *device, short *buffer, int sample_rate, int total_samples, const char *description)
{
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    int err;
    snd_pcm_uframes_t frames = 1024;

    if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
        printf("재생 장치 열기 실패: %s\n", snd_strerror(err));
        return err;
    }

    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handle, params);

    printf("스피커 장치 (%s) 지원 파라미터:\n", device);
    print_hw_params(handle, params);

    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, 2);
    unsigned int rate = sample_rate;
    snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0);
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, 0);

    if ((err = snd_pcm_hw_params(handle, params)) < 0)
    {
        printf("하드웨어 파라미터 설정 실패: %s\n", snd_strerror(err));
        snd_pcm_close(handle);
        return err;
    }

    printf("설정된 샘플레이트: %u Hz, 프레임 크기: %lu\n", rate, frames);

    printf("스피커 테스트: %s 재생 중...\n", description);
    for (int i = 0; i < total_samples / frames; i++)
    {
        if ((err = snd_pcm_writei(handle, buffer + (i * frames * 2), frames)) < 0)
        {
            if (err == -EPIPE)
            {
                snd_pcm_prepare(handle);
            }
            else
            {
                printf("재생 중 오류: %s\n", snd_strerror(err));
                break;
            }
        }
    }

    int remaining = total_samples % frames;
    if (remaining > 0)
    {
        snd_pcm_writei(handle, buffer + (total_samples - remaining) * 2, remaining);
    }

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    printf("재생 완료: %s\n", description);
    return 0;
}

// 톤 테스트 함수
int test_speaker_tone(const char *device)
{
    unsigned int sample_rate = 48000;
    int duration = 2;
    int total_samples = sample_rate * duration;
    short *buffer = malloc(total_samples * 2 * sizeof(short));
    if (!buffer)
    {
        printf("메모리 할당 실패\n");
        return -1;
    }

    generate_tone(buffer, sample_rate, 440, duration);
    int result = play_audio(device, buffer, sample_rate, total_samples, "440Hz 톤 (2초)");
    free(buffer);
    return result;
}

// 마이크 테스트 함수
int test_microphone(const char *device, const char *output_file)
{
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    int err;
    unsigned int sample_rate = 48000;
    snd_pcm_uframes_t frames = 1024;
    int record_seconds = 5;

    if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_CAPTURE, 0)) < 0)
    {
        printf("녹음 장치 열기 실패: %s\n", snd_strerror(err));
        return err;
    }

    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handle, params);

    printf("마이크 장치 (%s) 지원 파라미터:\n", device);
    print_hw_params(handle, params);

    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, 2);
    unsigned int rate = sample_rate;
    snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0);
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, 0);

    if ((err = snd_pcm_hw_params(handle, params)) < 0)
    {
        printf("하드웨어 파라미터 설정 실패: %s\n", snd_strerror(err));
        snd_pcm_close(handle);
        return err;
    }

    printf("설정된 샘플레이트: %u Hz, 프레임 크기: %lu\n", rate, frames);

    short *buffer = malloc(frames * 2 * sizeof(short));
    if (!buffer)
    {
        printf("메모리 할당 실패\n");
        snd_pcm_close(handle);
        return -1;
    }

    FILE *file = fopen(output_file, "wb");
    if (!file)
    {
        printf("파일 열기 실패: %s\n", output_file);
        free(buffer);
        snd_pcm_close(handle);
        return -1;
    }

    int total_samples = rate * record_seconds;
    int data_size = total_samples * 2 * sizeof(short);
    fwrite("RIFF", 1, 4, file);
    int chunk_size = data_size + 36;
    fwrite(&chunk_size, 4, 1, file);
    fwrite("WAVEfmt ", 1, 8, file);
    int fmt_size = 16;
    fwrite(&fmt_size, 4, 1, file);
    short audio_format = 1;
    fwrite(&audio_format, 2, 1, file);
    short channels = 2;
    fwrite(&channels, 2, 1, file);
    fwrite(&rate, 4, 1, file);
    int byte_rate = rate * channels * 2;
    fwrite(&byte_rate, 4, 1, file);
    short block_align = channels * 2;
    fwrite(&block_align, 2, 1, file);
    short bits_per_sample = 16;
    fwrite(&bits_per_sample, 2, 1, file);
    fwrite("data", 1, 4, file);
    fwrite(&data_size, 4, 1, file);

    printf("마이크 테스트: %d초 동안 녹음 중...\n", record_seconds);
    clock_t start_time = clock(); // 시작 시간 기록
    int iterations = total_samples / frames;
    int remaining = total_samples % frames;

    for (int i = 0; i < iterations; i++)
    {
        if ((err = snd_pcm_readi(handle, buffer, frames)) < 0)
        {
            if (err == -EPIPE)
            {
                snd_pcm_prepare(handle);
            }
            else
            {
                printf("녹음 중 오류: %s\n", snd_strerror(err));
                break;
            }
        }
        fwrite(buffer, sizeof(short), frames * 2, file);
    }

    if (remaining > 0)
    {
        if ((err = snd_pcm_readi(handle, buffer, remaining)) < 0)
        {
            if (err == -EPIPE)
            {
                snd_pcm_prepare(handle);
            }
            else
            {
                printf("녹음 중 오류 (남은 샘플): %s\n", snd_strerror(err));
            }
        }
        fwrite(buffer, sizeof(short), remaining * 2, file);
    }

    clock_t end_time = clock(); // 종료 시간 기록
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("녹음 완료. 실제 소요 시간: %.2f초\n", elapsed_time);

    fclose(file);
    free(buffer);
    snd_pcm_close(handle);
    printf("파일 저장: %s\n", output_file);
    return 0;
}

int main()
{
    const char *device = "hw:3,0";
    const char *output_file = "mic_test.wav";
    const char *alsa_test_file = "/usr/share/sounds/alsa/Front_Center.wav";

    if (test_speaker_tone(device) < 0)
    {
        return 1;
    }
    sleep(1);

    if (test_microphone(device, output_file) < 0)
    {
        return 1;
    }
    sleep(1);

    short *recorded_buffer;
    int recorded_rate, recorded_samples, recorded_channels;
    if (read_wav_file(output_file, &recorded_buffer, &recorded_rate, &recorded_samples, &recorded_channels) == 0)
    {
        play_audio(device, recorded_buffer, recorded_rate, recorded_samples, "녹음된 오디오");
        free(recorded_buffer);
    }
    sleep(1);

    short *alsa_buffer;
    int alsa_rate, alsa_samples, alsa_channels;
    if (read_wav_file(alsa_test_file, &alsa_buffer, &alsa_rate, &alsa_samples, &alsa_channels) == 0)
    {
        play_audio(device, alsa_buffer, alsa_rate, alsa_samples, "ALSA 테스트 파일 (Front_Center.wav)");
        free(alsa_buffer);
    }

    return 0;
}