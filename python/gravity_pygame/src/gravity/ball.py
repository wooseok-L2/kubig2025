import random

import pygame

Vec = pygame.Vector2


class Ball(pygame.sprite.Sprite):
    def __init__(self, game):
        self.game = game
        super().__init__()
        self.size = random.randint(10, 30)
        self.image = pygame.Surface((self.size * 2, self.size * 2))
        self.color = (
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255),
        )
        pygame.draw.circle(self.image, self.color, (self.size, self.size), self.size)
        self.image.set_colorkey((0, 0, 0))
        self.x = random.randint(0, 800)
        self.y = random.randint(0, 600)
        self.rect = self.image.get_rect()
        self.rect.center = Vec(self.x, self.y)  # type: ignore
        self.vel = Vec(random.randint(-10, 10), random.randint(-10, 10))
        self.mass = self.size
        self.acc = Vec(1, 0)

    def update(self):
        self.gravity()
        self.collide()
        self.vel -= self.acc
        if self.vel.length() > 30:
            self.vel = Vec(random.randint(-5, 5), random.randint(-5, 5))
        if self.vel.length() < 5:
            self.vel = Vec(random.randint(-5, 5), random.randint(-5, 5))
        self.rect.center += self.vel  # type: ignore
        if self.rect.x < 0:
            self.rect.x = 800
        if self.rect.x > 800:
            self.rect.x = 0
        if self.rect.y < 0:
            self.rect.y = 600
        if self.rect.y > 600:
            self.rect.y = 0

    def gravity(self):
        self.acc = Vec(0, 0)
        for ball in self.game.all_sprite.sprites():
            if not (ball == self):
                try:
                    distance = (Vec(self.rect.center) - Vec(ball.rect.center)).length()
                    direction = (
                        Vec(self.rect.center) - Vec(ball.rect.center)
                    ).normalize()
                    self.acc += 10 * direction * self.mass * ball.mass / (distance**2)
                except ZeroDivisionError:
                    pass

    def collide(self):
        other = pygame.sprite.spritecollide(self, self.game.all_sprite, False)  # type: ignore
        if len(other) > 1:
            temp = self.rect.center
            self.vel = (self.vel * self.size + other[1].vel * other[1].size) / (
                self.size + other[1].size
            )
            self.size = self.size + other[1].size
            if self.size > 100:
                self.size = 100
            self.image = pygame.Surface((self.size * 2, self.size * 2))
            self.color = (
                random.randint(0, 255),
                random.randint(0, 255),
                random.randint(0, 255),
            )
            pygame.draw.circle(
                self.image, self.color, (self.size, self.size), self.size
            )
            self.image.set_colorkey((0, 0, 0))
            self.rect = self.image.get_rect()
            self.rect.center = temp
            other[1].kill()
            del other[1]