#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include "WarmachineBLD.h"
#include "WarmachineKiwi.h"
#include "EmpireSoldier.h"

#define PI 3.14159265
#define QUANT_TREES 300

// C�digos das texturas
#define SNOW_FROSTBITE 6

#define QUANT_ENEMIES 8

int character ;

float alturaJanela = 600;
float larguraJanela = 600;

// Vari�veis para rota��o
double rotX = 0, rotY = 0, rotZ = 0;

// Array que guarda a posi��o das �rvores
int treesPosX[QUANT_TREES];
int treesPosZ[QUANT_TREES];

// Vari�vel que define qual a c�mera atual
int camera = 0; // 0 = Ortogonal; 1 = Perspectiva

// Vari�veis que atuar�o como rel�gio
time_t inicio;
time_t finalizacao;

void initTextures_Frostbite(){ // Fun��o para inicializar o uso das texturas
   // Ativa o uso de texturas
   glEnable (GL_TEXTURE_2D);

   // Informa quantas texturas ser�o carregadas
   glGenTextures(8, &textureId_WarmachineKiwi);

   // Carrega as texturas do rob�
   loadTextures_WarmachineKiwi();

   // Carrega as texturas do rob�
   CarregaTextura("snow_Frostbite.bmp", SNOW_FROSTBITE);

   // Carrega as texturas do inimigo
   loadTextures_EmpireSoldier();
}
void drawVegetation_Frostbite(){ // Fun��o de desenho das �rvores
    int i;
    
    // Troncos
    glColor3f(0.305, 0.156, 0.027);
    for(i=0; i<QUANT_TREES; i++){
        glPushMatrix();
        glTranslated(treesPosX[i], -0.32, treesPosZ[i]);
        
        glScaled(1.0, 5.0, 1.0);
        glutSolidCube(0.2);
        glPopMatrix();
    }
    
    // Folhas
    glColor3f(0.0, 0.2, 0.0);
    for(i=0; i<QUANT_TREES; i++){
        glPushMatrix();
        glTranslated(treesPosX[i], 2.5, treesPosZ[i]);
        glScaled(0.65, 2.5, 0.65);
        
        glEnable(GL_TEXTURE_2D);
        // Eu iria utilizar uma textura para as �rvores, mas a do ch�o combinou bem
        glBindTexture(GL_TEXTURE_2D, textureId_WarmachineKiwi[SNOW_FROSTBITE]);
        glBegin(GL_TRIANGLES);
        // Face da frente
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(-1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        
        // Face da direita
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(-1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        
        // Face de tr�s
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(-1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        
        // Face da esquerda
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, 1.0f, 0.0f);
        glTexCoord2f(-1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glPopMatrix();
    }
}

void initIlumination_Frostbite(){ // Fun��o para inicializar a ilumina��o
    // Luz do Mundo - Dia
    GLfloat worldD_PositionLight[4] = {0.0, 15.0, 0.0, 1.0};
    GLfloat worldD_AmbientLight[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat worldD_DifuseLight[4] = {0.7, 0.7, 0.7, 1.0};
    GLfloat worldD_SpecularLight[4] = {0.01, 0.01, 0.01, 1.0};

    // Luz do Mundo - Noite
    GLfloat worldN_PositionLight[4] = {0.0, 15.0, 0.0, 1.0};
    GLfloat worldN_AmbientLight[4] = {0.05, 0.05, 0.05, 1.0};
    GLfloat worldN_DifuseLight[4] = {0.07, 0.07, 0.07, 1.0};
    GLfloat worldN_SpecularLight[4] = {0.01, 0.01, 0.01, 1.0};

    // Luz do rob� 0
    GLfloat warmachinKiwi_PositionLight[4] = {pX_WarmachineKiwi, pY_WarmachineKiwi, pZ_WarmachineKiwi - 1.5, 1.0};
    GLfloat warmachineKiwi_DirectionLight[4] = {pX_WarmachineKiwi, pY_WarmachineKiwi, pZ_WarmachineKiwi - 5, 1.0};
    GLfloat warmachinKiwi_AmbientLight[4] = {0.7, 0.7, 0.7, 1.0};
    GLfloat warmachinKiwi_DifuseLight[4] = {0.7, 0.7, 0.7, 1.0};

    // Luz do rob� 1
    GLfloat warmachinBLD_PositionLight[4] = {pX_WarmachineBLD, pY_WarmachineBLD, pZ_WarmachineBLD - 1.5, 1.0};
    GLfloat warmachineBLD_DirectionLight[4] = {pX_WarmachineBLD, pY_WarmachineBLD + 0.5, pZ_WarmachineBLD - 2, 1.0};
    GLfloat warmachinBLD_AmbientLight[4] = {0.7, 0.7, 0.7, 1.0};
    GLfloat warmachinBLD_DifuseLight[4] = {0.7, 0.7, 0.7, 1.0};

    // Par�metros da luz diurna
    glLightfv(GL_LIGHT2, GL_POSITION, worldD_PositionLight);
    glLightfv(GL_LIGHT2, GL_AMBIENT, worldD_AmbientLight);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, worldD_DifuseLight);
    glLightfv(GL_LIGHT2, GL_SPECULAR, worldD_SpecularLight);

    // Par�metros da luz noturna
    glLightfv(GL_LIGHT0, GL_POSITION, worldN_PositionLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, worldN_AmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, worldN_DifuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, worldN_SpecularLight);

    if(character == 0){
        // Par�metros da luz do rob� 0
        glLightfv(GL_LIGHT1, GL_POSITION, warmachinKiwi_PositionLight);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, warmachineKiwi_DirectionLight);
        glLightfv(GL_LIGHT1, GL_AMBIENT, warmachinKiwi_AmbientLight);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, warmachinKiwi_DifuseLight);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 16.5);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0);
    }else if(character == 1){
        // Par�metros da luz do rob� 1
        glLightfv(GL_LIGHT1, GL_POSITION, warmachinBLD_PositionLight);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, warmachineBLD_DirectionLight);
        glLightfv(GL_LIGHT1, GL_AMBIENT, warmachinBLD_AmbientLight);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, warmachinBLD_DifuseLight);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 13.5);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0);
    }


    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, worldN_AmbientLight);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // Habilita a configura��o de luz inicial
    glEnable(GL_LIGHT2);
    glClearColor(0.0, 0.7, 0.93, 1.0);
}
void initVegetation_Frostbite(){ // Inicializa a posi��o das �rvores
    int i;

    for(i = 0; i < QUANT_TREES; i++){
        double x = -50 + rand()%100;
        double z = -50 + rand()%100;

        treesPosX[i] = x;
        treesPosZ[i] = z;
    }
}
void initChase_Frostbite(){ // Inicializa a posi��o do inimigo
    pX_EmpireSoldier = -50 + rand()%100;
    pZ_EmpireSoldier = -50 + rand()%100;

    colided_EmpireSoldier = 0;
    canDraw_EmpireSoldier = 1;
}

void draw_Frostbite(){ // Fun��es de desenho do campo de batalha
    // Ch�o de neve
    glPushMatrix();
        // Quad para textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId_WarmachineKiwi[SNOW_FROSTBITE]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 18.0f); glVertex3f(-50.0f, -0.9f, 50.0f);
            glTexCoord2f(18.0f, 18.0f); glVertex3f(50.0f, -0.9f, 50.0f);
            glTexCoord2f(18.0f, 0.0f); glVertex3f(50.0f, -0.9f, -50.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -0.9f, -50.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // �rvores
    drawVegetation_Frostbite();
}

void reshape_Frostbite(int width, int height) { // Fun��o de redimensionamento de tela

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    alturaJanela = (float)height;
    larguraJanela = (float)width;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(character == 1){
        if(camera == 0) isometricCamera_WarmachineBLD((GLfloat)width / (GLfloat)height);
        else if(camera == 1) perspectiveCamera_WarmachineBLD((GLfloat)width / (GLfloat)height);
    }else if(character == 0){
        if(camera == 0) isometricCamera_WarmachineKiwi((GLfloat)width / (GLfloat)height);
        else if(camera == 1) perspectiveCamera_WarmachineKiwi((GLfloat)width / (GLfloat)height);
    }

    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void display_Frostbite(void){ // Fun��o para desenhar na tela
    // Cor da limpeza da tela
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Manda desenhar
    glLoadIdentity();
    if(character == 1){
        if(camera == 0) isometricCamera_WarmachineBLD((larguraJanela/alturaJanela));
        else if (camera == 1) perspectiveCamera_WarmachineBLD((larguraJanela/alturaJanela));

    }else if(character == 0){
        if(camera == 0) isometricCamera_WarmachineKiwi((larguraJanela/alturaJanela));
        else if (camera == 1) perspectiveCamera_WarmachineKiwi((larguraJanela/alturaJanela));
    }
    // Aplica as rota��es
    glRotated(rotX, 1.0, 0.0, 0.0);
    glRotated(rotY, 0.0, 1.0, 0.0);
    glRotated(rotZ, 0.0, 0.0, 1.0);

    // Rotinas de desenho
    glPushMatrix();
        draw_Frostbite();
    glPopMatrix();
    glPushMatrix();
        draw_EmpireSoldier();
    glPopMatrix();
    glPushMatrix();
        if(character == 0){
            draw_WarmachineKiwi();
        }else if(character == 1){
            draw_WarmachineBLD();
        }

    glPopMatrix();

    // Verifica se o programa pode acabar,
    // mostra o tempo necess�rio
    if(quantDefeated_EmpireSoldier >= QUANT_ENEMIES){
        time(&finalizacao);

        printf("\n\n\n");
        printf("#=========================#\n");
        printf("|        GAME OVER        |\n");
        printf("#=========================#\n");
        printf("Tempo gasto: %.2lf segundos para encontrar %d fugitivos.\n", difftime(finalizacao, inicio), QUANT_ENEMIES);

        exit(0);
    }

    glutSwapBuffers();
}

// Fun��o para o teclado
void keyboard_Frostbite(unsigned char key, int x, int y){
    // Fun��es do teclado no modo controle
    if (camera == 1){
        switch(key){
            case 'x':
                rotX += 5;
            break;
            case 'X':
                rotX -= 5;
            break;

            case 'y':
                rotY += 5;
            break;
            case 'Y':
                rotY -= 5;
            break;

            case 'z':
                rotZ += 5;
            break;
            case 'Z':
                rotZ -= 5;
            break;

            case 'b':
            case 'B':
                if(character == 0){
                    pX_WarmachineKiwi = pX_EmpireSoldier - 2.0;
                    pZ_WarmachineKiwi = pZ_EmpireSoldier - 2.0;
                }
                else if(character == 1){
                    pX_WarmachineBLD = pX_EmpireSoldier - 2.0;
                    pZ_WarmachineBLD = pZ_EmpireSoldier - 2.0;
                }
            break;

            case 'o':
            case 'O':
                if(character == 0){
                    pX_WarmachineKiwi = 0;
                    pZ_WarmachineKiwi = 0;
                }
                else if(character == 1){
                    pX_WarmachineBLD = 0;
                    pZ_WarmachineBLD = 0;
                }
            break;

            case 'R':
            case 'r':
                rotX =0;
                rotY = 0;
                rotZ = 0;
            break;

            // Troca o modo da camera
            case 'm':
            case 'M':
                if(camera == 1) camera = 0;
                else camera = 1;

                rotX =0;
                rotY = 0;
                rotZ = 0;
            break;

            // Controle em perspectiva
            case 'w':
            case 'W':
                if(character == 0){
                    moveFoward_WarmachineKiwi();
                    glutIdleFunc(walk_WarmachineKiwi);
                }else if(character == 1){
                    moveFoward_WarmachineBLD();
                    glutIdleFunc(walk_WarmachineBLD);
                }
            break;

            case 's':
            case 'S':
                if(character == 0){
                    moveBackward_WarmachineKiwi();
                    glutIdleFunc(walk_WarmachineKiwi);
                }else if(character == 1){
                    moveBackward_WarmachineBLD();
                    glutIdleFunc(walk_WarmachineBLD);
                }
            break;

            case 'd':
            case 'D':
                if(character == 0){
                    turnRight_WarmachineKiwi();
                    glutIdleFunc(walk_WarmachineKiwi);
                }else if(character == 1){
                    turnRight_WarmachineBLD();
                    glutIdleFunc(walk_WarmachineBLD);
                }
            break;

            case 'a':
            case 'A':
                if (character == 0) {
                    turnLeft_WarmachineKiwi();
                    glutIdleFunc(walk_WarmachineKiwi);
                }else if(character == 1){
                    turnLeft_WarmachineBLD();
                    glutIdleFunc(walk_WarmachineBLD);
                }
            break;

            default:
            break;
        }
    }
    // Fun��es de controle no modo mapa
    else if(camera == 0){
    switch(key){
            case 'x':
                rotX += 5;
            break;
            case 'X':
                rotX -= 5;
            break;

            case 'y':
                rotY += 5;
            break;
            case 'Y':
                rotY -= 5;
            break;

            case 'z':
                rotZ += 5;
            break;
            case 'Z':
                rotZ -= 5;
            break;

            case 'R':
            case 'r':
                rotX =0;
                rotY = 0;
                rotZ = 0;
            break;

            // Troca o modo da camera
            case 'm':
            case 'M':
                if(camera == 1) camera = 0;
                else camera = 1;

                rotX =0;
                rotY = 0;
                rotZ = 0;
            break;

            // Controle em perspectiva
            case 'w':
            case 'W':
                if(character == 0) panY_WarmachineKiwi--;
                else if(character == 1) panY_WarmachineBLD--;
            break;

            case 's':
            case 'S':
                if(character == 0) panY_WarmachineKiwi++;
                else if(character == 1) panY_WarmachineBLD++;
            break;

            case 'd':
            case 'D':
                if(character == 0) panX_WarmachineKiwi--;
                else if(character == 1) panX_WarmachineBLD--;
            break;

            case 'a':
            case 'A':
                if(character == 0) panX_WarmachineKiwi++;
                else if(character == 1) panX_WarmachineBLD++;
            break;

            // Controle de Dia-Noite
            case 'L': // Dia
                glDisable(GL_LIGHT0);
                glDisable(GL_LIGHT1);
                glEnable(GL_LIGHT2);

                glClearColor(0.0, 0.7, 0.93, 1.0);
            break;

            case 'l': // Noite
                glEnable(GL_LIGHT0);
                glEnable(GL_LIGHT1);
                glDisable(GL_LIGHT2);

                glClearColor(0.0, 0.0, 0.0, 1.0);
            break;

            default:
            break;
        }
    }
    glutPostRedisplay();
}
void keyboardUp_Frostbite(unsigned char key, int x, int y){
    glutIdleFunc(NULL);
    glutPostRedisplay();
}

int main(int argc, char **argv){
    srand(time(NULL));

    // Apresenta��o
    printf("__          __                             _     _     \n");
    printf("\\ \\        / /                            | |   (_)   \n");
    printf(" \\ \\  /\\  / /_ _ _ __ _ __ ___   __ _  ___| |__  _ _ __   ___   \n");
    printf("  \\ \\/  \\/ / _` | '__| '_ ` _ \\ / _` |/ __| '_ \\| | '_ \\ / _ \\ \n");
    printf("   \\  /\\  / (_| | |  | | | | | | (_| | (__| | | | | | | |  __/ \n");
    printf("    \\/  \\/ \\__,_|_|  |_| |_| |_|\\__,_|\\___|_| |_|_|_| |_|\\___| \n");
    printf("              ___  __   __   __  ___  __    ___  ___ \n");
    printf("             |__  |__) /  \\ /__`  |  |__) |  |  |__  \n");
    printf("             |    |  \\ \\__/ .__/  |  |__) |  |  |___ \n");

    printf("Objetivo:\n Capturar %d fugitivos;\n\n", QUANT_ENEMIES);

    printf("Controles:\nM - Troca entre visao de controle e visao tatica;\n\n");
    printf("Visao de Controle: W,A,S,D - Controla Warmachine;\n");
    printf("Visao Tatica: W,A,S,D - Desloca visao tatica;\n\n");

    printf("Funcoes de Desenvolvedor:\nX,Y,Z - Rotaciona a cena;\nR - Reseta as rotacoes de cena;\nL\\l - Troca modo de iluminacao (somente em visao tatica);\nB - Teleporta para posicao proxima a do inimigo;\nO - Teleporta para origem;\n");

    printf("\nEntre com 0 para usar Warmachine-KIWI;\nEntre com 1 para usar Warmachine-BLD;\n>>");

    scanf("%d", &character);

    // Inicializa��o da GLUT
    glutInit (&argc, argv);

    // Defini��es da janela de desenho
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH) ;
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutInitWindowPosition(550, 50);
    glutCreateWindow("Warmachine: Frostbite");

    // Defini��o da fun��o de desenho
    glutDisplayFunc(display_Frostbite);
    // Fun��o de teclado
    glutKeyboardFunc(keyboard_Frostbite);
    glutKeyboardUpFunc(keyboardUp_Frostbite);
    // Fun��o de redimensionamento
    glutReshapeFunc(reshape_Frostbite);

    // Rotinas de inicializa��o
    initVegetation_Frostbite();
    initTextures_Frostbite();
    initIlumination_Frostbite();
    initChase_Frostbite();

    // Inicia a contagem de tempo
    time(&inicio);
    glutIdleFunc(NULL);

    // Loop da GLUT
    glutMainLoop();

    return 0;
}
