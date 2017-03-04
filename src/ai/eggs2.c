#include "ai.h"

#include <genesis.h>
#include "audio.h"
#include "player.h"
#include "stage.h"
#include "tables.h"
#include "tsc.h"
#include "camera.h"
#include "effect.h"

void onspawn_deaddragon(Entity *e) {
	e->frame = 5;
	e->attack = 0;
}

void ai_dragon_zombie(Entity *e) {
	if (e->health < 950 && e->state < 50) {
		sound_play(SND_BIG_CRASH, 5);
		effect_create_damage(e->damage_value, sub_to_pixel(e->x), sub_to_pixel(e->y));
		e->damage_time = e->damage_value = 0;
		effect_create_smoke(e->x << CSF, e->y << CSF);
		entity_drop_powerup(e);
		
		e->nflags &= ~NPC_SHOOTABLE;
		e->attack = 0;
		
		e->frame = 5;	// dead
		e->state = 50;	// dead
	}
	
	switch(e->state) {
		case 0:
		case 1:		// ready
		{
			ANIMATE(e, 30, 0,1);
			
			if (e->timer == 0) {
				if (PLAYER_DIST_X(112 << CSF)) {
					e->state = 2;
					e->timer = 0;
				}
			} else {
				e->timer--;
			}
		}
		break;
		
		case 2:		// flashing, prepare to fire
		{
			FACE_PLAYER(e);
			
			e->timer++;
			e->frame = (e->timer & 4) ? 2 : 3;
			
			if (e->timer > TIME(30))
				e->state = 3;
		}
		break;
		
		case 3:
		{
			e->state = 4;
			e->timer = 0;
			e->frame = 4;
			
			// save point we'll fire at--these enemies don't update
			// the position of their target for each shot
			e->x_mark = player.x;
			e->y_mark = player.y;
		}
		case 4:
		{
			e->timer++;
			
			if (e->timer < TIME(40) && (e->timer % 8) == 1) {
				//Entity *fire = entity_create(e->x, e->y, OBJ_DRAGON_ZOMBIE_SHOT, 0);
				//ThrowEntity(fire, e->xmark, e->ymark, 6, 0x600);
				FIRE_ANGLED_SHOT(OBJ_DRAGON_ZOMBIE_SHOT, e->x, e->y, 
						e->dir ? A_RIGHT + 6 : A_LEFT - 6, SPEED(0x500));
				
				sound_play(SND_SNAKE_FIRE, 3);
			}
			
			if (e->timer > TIME(60)) {
				e->state = 1;
				e->frame = 0;
				e->timer = (random() % TIME(100)) + TIME(100);	// random time till can fire again
			}
		}
		break;
	}
}

void ai_falling_spike_small(Entity *e) {
	switch(e->state) {
		case 0:
		{
			e->x_mark = e->x;
			
			if (PLAYER_DIST_X(12 << CSF))
				e->state = 1;
		}
		break;
		
		case 1:		// shaking
		{
			if (++e->animtime >= 12)
				e->animtime = 0;
			
			e->x = e->x_mark;
			if (e->animtime >= 6) e->x += (1 << CSF);
			
			if (++e->timer > TIME(30)) {
				e->state = 2;	// fall
				e->frame = 1;	// slightly brighter frame at top
			}
		}
		break;
		
		case 2:		// falling
		{
			e->y_speed += SPEED(0x20);
			LIMIT_Y(SPEED(0xC00));
			
			e->x_next = e->x;
			e->y_next = e->y + e->y_speed;
			if (collide_stage_floor(e)) {
				if (!controlsLocked)	// no sound in ending cutscene
					sound_play(SND_BLOCK_DESTROY, 5);
				
				//SmokeClouds(o, 4, 2, 2);
				//effect(e->CenterX(), e->CenterY(), EFFECT_BOOMFLASH);
				e->state = STATE_DELETE;
			}
			e->y = e->y_next;
		}
		break;
	}
}


void ai_falling_spike_large(Entity *e) {
	switch(e->state) {
		case 0:
		{
			e->x_mark = e->x;
			
			if (PLAYER_DIST_X(12 << CSF))
				e->state = 1;
		}
		break;
		
		case 1:		// shaking
		{
			if (++e->animtime >= 12)
				e->animtime = 0;
			
			e->x = e->x_mark;
			if (e->animtime >= 6)	// scuttle:: big spikes shake in the other direction
				e->x -= (1 << CSF);
			
			if (++e->timer > TIME(30)) {
				e->state = 2;	// fall
				e->frame = 1;	// slightly brighter frame at top
				
				// Search for a Dragon Zombie underneath
				Entity *dragon = entityList;
				while(dragon) {
					if(dragon->type == OBJ_DRAGON_ZOMBIE && dragon->state < 50 &&
							dragon->x > e->x - 0x2000 && dragon->x < e->x + 0x2000) break;
					dragon = dragon->next;
				}
				if(dragon) e->linkedEntity = dragon;
			}
		}
		break;
		
		case 2:		// falling
		{
			e->y_speed += SPEED(0x20);
			LIMIT_Y(SPEED(0xC00));
			
			if (e->y + (e->hit_box.bottom<<CSF) < player.y + (player.hit_box.top<<CSF)) {	
				// could fall on player
				e->nflags &= ~NPC_SPECIALSOLID;
				e->attack = 127;	// ouch!
			} else {	// player could only touch side from this position
				e->nflags |= NPC_SPECIALSOLID;
				e->attack = 0;
			}
			
			// Kill that one Dragon Zombie
			if(e->linkedEntity && entity_overlapping(e, e->linkedEntity)) {
				e->linkedEntity->health -= 127;
				e->linkedEntity->damage_value = -127;
				e->linkedEntity = NULL;
			}
			
			e->x_next = e->x;
			e->y_next = e->y + e->y_speed;
			if (++e->timer > 8 && collide_stage_floor(e)) {
				e->nflags |= NPC_SPECIALSOLID;
				e->attack = 0;
				e->y_speed = 0;
				
				e->state = 3;	// fall complete
				e->timer = 0;
				
				sound_play(SND_BLOCK_DESTROY, 5);
				//SmokeClouds(o, 4, 2, 2);
				
				//effect(e->CenterX(), e->y + (sprites[e->sprite].block_d[0].y << CSF),
				//	EFFECT_STARSOLID);
			}
			e->y = e->y_next;
		}
		break;
		
		case 3:		// hit ground
		{
			if (++e->timer > 4) {	// make it destroyable
				e->eflags |= NPC_SHOOTABLE;
				e->nflags |= NPC_SHOOTABLE;
				e->eflags &= ~NPC_INVINCIBLE;
				e->nflags &= ~NPC_INVINCIBLE;
				e->state = 4;
			}
		}
		break;
	}
}

void ai_counter_bomb(Entity *e) {
	switch(e->state) {
		case 0:
		{
			e->state = 1;
			e->y_mark = e->y;
			
			e->timer = random() % 50;
			e->timer2 = 0;
		}
		case 1:
		{	// desync if multiple enemies
			if (e->timer == 0) {
				e->timer = 0;
				e->state = 2;
				e->y_speed = SPEED(0x300);
			} else {
				e->timer--;
			}
		}
		break;
		
		case 2:		// ready
		{
			if (PLAYER_DIST_X(80 << CSF) || e->damage_time) {
				e->state = 3;
				e->timer = 0;
				e->alwaysActive = TRUE;
			}
		}
		break;
		
		case 3:		// counting down...
		{
			if (e->timer == 0) {
				if (e->timer2 < 5) {
					Entity *number = entity_create(e->x + (8 << CSF), e->y + (16 << CSF),
												  OBJ_COUNTER_BOMB_NUMBER, 0);
					number->frame = e->timer2++;
					e->timer = 60;
				} else {
					// expand bounding box to cover explosion area
					e->hidden = TRUE;
					e->hit_box.left = 128;
					e->hit_box.top = 100;
					e->hit_box.right = 128;
					e->hit_box.bottom = 100;
					e->attack = 30;
					
					e->y_speed = 0;
					e->state = 4;
					
					// make kaboom
					sound_play(SND_EXPLOSION1, 5);
					camera_shake(20);
					// Just override any other smoke that might be going on
					effects_clear_smoke();
					SMOKE_AREA((e->x>>CSF) - 64, (e->y>>CSF) - 50, 128, 100, MAX_SMOKE);
					
					return;
				}
			} else {
				e->timer--;
			}
		}
		break;
		
		case 4:		// exploding (one frame only to give time for bbox to damage player)
			e->state = STATE_DELETE;
			return;
	}
	
	// The sprite is a bit large, no point in refreshing our tiles when not visible
	if(entity_on_screen(e)) {
		ANIMATE(e, 4, 0,1,2);
	}
	
	if (e->state == 2 || e->state == 3) {
		e->y_speed += (e->y > e->y_mark) ? -0x10 : 0x10;
		LIMIT_Y(0x100);
	}
}

void ai_counter_bomb_number(Entity *e) {
	switch(e->state) {
		case 0:
		{
			sound_play(SND_COMPUTER_BEEP, 5);
			e->state = 1;
		}
		case 1:
		{
			e->x += (1 << CSF);
			if (++e->timer > 8) {
				e->state = 2;
				e->timer = 0;
			}
		}
		break;
		
		case 2:
		{
			if (++e->timer > TIME(30))
				e->state = STATE_DELETE;
		}
		break;
	}
}
