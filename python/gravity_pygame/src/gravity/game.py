import time

import pygame

from .ball import Ball


class UI(pygame.sprite.Sprite):
    def __init__(self, game):
        super().__init__()
        self.game = game
        self.font = pygame.font.SysFont(None, 50)
        self.image = None
        self.rect = None
        self.start_time = time.time()

    def update(self):
        elapsed_time = time.time() - self.start_time
        ui_text = f"Elapsed Time : {elapsed_time:.2f}, ball Count: {len(self.game.all_sprite)}"
        self.image = self.font.render(ui_text, True, (0, 0, 0))
        self.rect = self.image.get_rect(topleft=(10, 10))

    def draw(self, surface):
        surface.blit(self.image, self.rect)


class Game:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((800, 600))
        self.game_active = True
        self.clock = pygame.time.Clock()
        self.fps = 60
        self.all_sprite = pygame.sprite.Group()
        self.ui = UI(self)

    def update(self):
        self.ui.update()
        if len(self.all_sprite) < 20:
            ball = Ball(self)
            self.all_sprite.add(ball)
        self.all_sprite.update()

    def draw(self):
        self.screen.fill((255, 255, 255))
        self.all_sprite.draw(self.screen)
        self.ui.draw(self.screen)
        pygame.display.flip()

    def run(self):
        while True:
            self.clock.tick(self.fps)
            if self.game_active:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        pygame.quit()
                        exit()
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_q:
                            self.game_active = False
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        print("mouse button down")
                        print(event.dict)
                        print(event.dict["pos"][0], event.dict["pos"][1])
                self.update()  # 게임 로직에 필요한 내부 변수...
                self.draw()  # 화면 출력을 담당.
            else:
                break