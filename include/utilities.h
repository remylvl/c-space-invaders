#include "entities.h"

//GETTERS
//getX
float getXPlayer(Player *p);
float getXEntity(Entity *e);
float getXEnemy(Enemy *e);

//getY
float getYPlayer(Player *p);
float getYEntity(Entity *e);
float getYEnemy(Enemy *e);

//getVx
float getVxPlayer(Player *p);
float getVxEntity(Entity *e);
float getVxEnemy(Enemy *e);

//getVy
float getVyPlayer(Player *p);
float getVyEntity(Entity *e);
float getVyEnemy(Enemy *e);

//getW
int getWPlayer(Player *p);
int getWEntity(Entity *e);
int getWEnemy(Enemy *e);

//getH
int getHPlayer(Player *p);
int getHEntity(Entity *e);
int getHEnemy(Enemy *e);

//SETTERS
//setX
void setXPlayer(Player *p, float x);
void setXEntity(Entity *e, float x);
void setXEnemy(Enemy *e, float x);

//setY
void setYPlayer(Player *p, float y);
void setYEntity(Entity *e, float y);
void setYEnemy(Enemy *e, float y);

//setVx
void setVxPlayer(Player *p, float vx);
void setVxEntity(Entity *e, float vx);
void setVxEnemy(Enemy *e, float vx);

//setVy
void setVyPlayer(Player *p, float vy);
void setVyEntity(Entity *e, float vy);
void setVyEnemy(Enemy *e, float vy);

//setW
void setWPlayer(Player *p, int w);
void setWEntity(Entity *e, int w);
void setWEnemy(Enemy *e, int w);

//setH
void setHPlayer(Player *p, int h);
void setHEntity(Entity *e, int h);
void setHEnemy(Enemy *e, int h);

//Autres
bool collisionBulletEnemy(Enemy *e, Entity *bullet);
bool collisionPlayerEnemy(Player *p, Enemy *e);