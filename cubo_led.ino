/*
Referência
http://viciadosemarduino.blogspot.com/2015/01/cubo-de-leds-3x3x3.html
*/
#include <LedCube.h>
#define SIZE 3
#define COLS (SIZE*SIZE)

byte levelPins[SIZE] = {10,11,12};
byte colPins[COLS] = {0,2,3,4,5,6,7,8,9};
LedCube cube(SIZE, levelPins, colPins);

void setup ()
{}
void loop ()
{
    delay(10);

    // círculo em torno de cubo de baixo para cima
    for(byte linha=0; linha<cube.getLevels(); linha++)
    {
      cube.lightPerimeter(linha, 1, 75);
    }
    // círculo em torno de cubo de cima para baixo
    for(byte linha=cube.getLevels(); linha>0; linha--)
    {
      cube.lightPerimeter(linha, 1, 75);
    }
    
    // acender uma luz em um sinal de tempo, uma luz de cada vez
    for(byte level=0; level<cube.getLevels(); level++)
    {
        for(byte col=0; col<cube.getCols(); col++)
        {
            cube.lightPulse(level, col, 100);
        }
    }
    
    // um nível de luz de cada vez, o aumento da velocidade
    for(byte d=25; d>2; d-=2)
    {
        for(byte l=1; l <= cube.getLevels(); l++)
        {
            cube.lightLevel(l, d);
        }
    }
    
    // acender cada linha em cada nível
    for(byte level=1; level<=cube.getLevels(); level++)
    {
        for(byte row=1; row<=cube.getLevels()*2; row++)
        {
            cube.lightRow(row, level);
        }
    }
    
    // acender cada plano
    for(byte i=3; i; i--)
    {
        for(byte row=1; row<=cube.getLevels()*2; row++)
        {
            cube.lightPlane(row, 10*i);
        }
    }
    
    // luz aleatória simples de cada vez
    cube.randomLight(random(25,100),100);
    
    // coluna aleatória
    for(byte x=0; x<=15; x++)
    {
        cube.lightDrop(random(0,cube.getCols()), random(50,150));
    }
    
    // círculo em torno de cubo em um nível aleatório
    for(byte x=0; x<=5; x++)
    {
        cube.lightPerimeter(random(0,cube.getLevels()), random(1,5), random(25,100));
    }
    
    // acender cada rosto
    byte planes[] = {cube.getLevels()+1,cube.getLevels(),cube.getLevels()*2,1};
    for(byte i=5; i; i--)
    {
        for(byte p=0; p<sizeof(planes); p++)
        {
            cube.lightPlane(planes[p], 5*i);
        }
    }
    
    // colunas aleatórias
    cube.randomColumn(25);
    
    // desativar uma única coluna aleatoriamente
    cube.enableBuffer();
    for(byte c=0; c<30; c++)
    {
        cube.fillBuffer();
        cube.invertBuffer();
        cube.randomColumn();
        cube.drawBuffer(7);
    }
    cube.enableBuffer(false);
    
    // dentro e fora
    for(byte c=1, d=0; c<=10; c++)
    {
        if(c%2 == 0)
        {
            for(d=0; d<20; d++)
            {
                cube.lightColumn(2,1);
                cube.lightColumn(4,1);
                cube.lightColumn(6,1);
                cube.lightColumn(8,1);
            }
        }
        else if(c%4 == 1)
        {
            for(d=0; d<30; d++)
            {
                cube.lightColumn(1,1);
                cube.lightColumn(3,1);
                cube.lightColumn(7,1);
                cube.lightColumn(9,1);
            }
        }
        else
        {
            for(d=0; d<70; d++)
            {
                cube.lightColumn(5,1);
            }
        }
    }
    
    // diamante e caixa
    byte diamond[] = {0,4,  1,1, 1,3, 1,4, 1,5, 1,7,   2,4};
    byte box[] = {
        2,0, 2,1, 2,2, 2,3, 2,5, 2,6, 2,7, 2,8,
        1,0, 1,2, 1,6, 1,8,
        0,0, 0,1, 0,2, 0,3, 0,5, 0,6, 0,7, 0,8
    };
    cube.lightSequence(box, sizeof(box), 200);
    cube.lightSequence(diamond, sizeof(diamond), 400);
    
    // efeito helicóptero
    byte topSeq[8] = {0,3,6,7,8,5,2,1};
    byte botSeq[8] = {8,5,2,1,0,3,6,7};
    for(byte loops = 0, delay = 50; loops<=8; loops++)
    {
        for(byte s=0; s<8; s++)
        {
            byte seq[] = {2,topSeq[s], 1,4, 0,botSeq[s]};
            cube.lightSequence(seq, sizeof(seq), delay);
        } 
        if(loops < 5) delay-=10;  else delay += 10;
    }
    
    // desligar uma luz de cada vez
    cube.enableBuffer();
    cube.fillBuffer();
    cube.drawBuffer(25);
    for(byte w=0, l, c, max = cube.getNumLights(); w<max; )
    {
        // limite inferior é, inclusive, superior é exclusivo
        l = random(0, cube.getLevels());
        c = random(0, cube.getCols());
        
        if(cube.getBufferAt(l,c) == HIGH)
        {
            cube.lightOff(l,c);
            cube.drawBuffer(5);
            w++;
        }
    }
    cube.enableBuffer(false);
    
    //rojão
    byte rojao1[] = {0,4, 1,4, 2,4 };
    cube.lightSequence(rojao1, sizeof(rojao1), 1, 100);
    byte rojao2[] = { 2,0, 2,1, 2,2, 2,3, 2,5, 2,6, 2,7, 2,8};
    cube.lightSequence(rojao2, sizeof(rojao2), 20);
    byte rojao3[] = { 1,0, 1,1, 1,2, 1,3, 1,5, 1,6, 1,7, 1,8};
    cube.lightSequence(rojao3, sizeof(rojao3), 20);
    byte rojao4[] = { 0,0, 0,1, 0,2, 0,3, 0,5, 0,6, 0,7, 0,8};
    cube.lightSequence(rojao4, sizeof(rojao4), 20);
    
}
