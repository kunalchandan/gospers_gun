#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <random>

const int len = 128;
const int sca = 4;

int IX(int x, int y) {
	return (x + (y * len));
}

int main()
{
	bool* now = new bool[len*len];
	bool* nex = new bool[len*len];

	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			now[IX(y, x)] = rand() % 2;
		}
	}

	al_init();
	al_init_font_addon();
	ALLEGRO_DISPLAY* display = al_create_display(len* sca, len * sca);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	ALLEGRO_COLOR c = { 0, 0, 0, 1 };
	for (int t = 0; t < 1000; t++) {
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		std::cout << "step: " << t << std::endl;
		
		// Check All cells
		for (int x = 0; x < len; x++) {
			for (int y = 0; y < len; y++) {
				int sum = 0;
				int sx = (x == 0)? 0:-1, ex = (x == len-1)? 0:1;
				int sy = (y == 0)? 0:-1, ey = (y == len-1)? 0:1;
				// Sum up all the number of living cells around a cell
				for (int i = sx; i <= ex; i++) {
					for (int j = sy; j <= ey; j++) {
						if (now[IX(y + j, x + i)]) {
							sum++;
						}
					}
				}
				if (now[IX(y, x)]) {
					sum--;
				}

				// Check if a cell lives or dies
				if (now[IX(y, x)] && sum < 2) {
					nex[IX(y, x)] = false;
				}
				else if (now[IX(y, x)] && sum >= 4) {
					nex[IX(y, x)] = false;
				}
				else if (now[IX(y, x)] && sum < 4) {
					nex[IX(y, x)] = true;
				}
				else if (!now[IX(y, x)] && sum == 3) {
					nex[IX(y, x)] = true;
				}

				// Define the colour that cell will become
				if (nex[IX(y, x)]) {
					c = al_map_rgb(255, 255, 255);
				}
				else {
					c = al_map_rgb(0, 0, 0);
				}

				// Draw that colour to the screen
				for (int i = 0; i < sca; i++) {
					for (int j = 0; j < sca; j++) {
						al_draw_pixel(x * sca + i, y * sca + j, c);
					}
				}
			}
		}

		// Update now
		for (int x = 0; x < len; x++) {
			for (int y = 0; y < len; y++) {
				now[IX(y, x)] = nex[IX(y, x)];
			}
		}
	}

	al_rest(5.0);
	return 0;
}

