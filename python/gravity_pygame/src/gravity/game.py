import pygame

class Game:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((800,600))
        self.game_active = True
    
    def update(self):
        pass
    
    def update_screen(self):
        self.screen.fill((255,255,255))
        pygame.display.flip()
        
    def run(self):
        while True:
            if self.game_active:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        pygame.quit()
                        exit()
                self.update() 
                self.update_screen()
            else:
                break   