FROM python:3.10-slim

WORKDIR /app

RUN apt update && apt install -y \
    gcc \
    g++ \
    libffi-dev \
    && rm -rf /var/lib/apt/lists/*


COPY requirments.txt ./
RUN pip install --no-cache-dir -r requirments.txt

COPY . .

EXPOSE 5000

CMD ["flask", "run", "--host=0.0.0.0", "--port=5000"]