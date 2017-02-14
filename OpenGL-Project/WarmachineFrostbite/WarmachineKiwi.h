//============================================//
//        WARMACHINE "KIWI" OF LUNASTRAD
//============================================//
// Defini��es b�sicas
#define PI 3.14159265
#define NUMBER_OF_TEXTURES_WARMACHHINEKIWI 6

// C�digos das texturas
// Perna
#define FOOT_WARMACHINEKIWI 0
#define KNEE_WARMACHINEKIWI 1

// Corpo
#define FACE_WARMACHINEKIWI 2
#define EMBLEM_WARMACHINEKIWI 3

// Arma
#define GUNFRONT_WARMACHINEKIWI 4
#define GUNFACE_WARMACHINEKIWI 5


// Fun��es e defini��es para trabalhar com texturas
GLuint textureId_WarmachineKiwi[NUMBER_OF_TEXTURES_WARMACHHINEKIWI];
typedef struct BMPImagem{
    int   width;
    int   height;
    char *data;
}BMPImage;
void getBitmapImageData( char *pFileName, BMPImage *pImage ){
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
		printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
		printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
		printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
		printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

	// Calculate the image's total size in bytes. Note how we multiply the
	// result of (width * height) by 3. This is becuase a 24 bit color BMP
	// file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
	// Finally, rearrange BGR to RGB
	//

	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i+2];
		pImage->data[i+2] = charTemp;
    }
}
void CarregaTextura(char* Filename, int posText){

    BMPImage textura;

    getBitmapImageData(Filename, &textura);

    glBindTexture (GL_TEXTURE_2D, textureId_WarmachineKiwi[posText]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
}


//============================================//
//             VARI�VEIS GLOBAIS
//============================================//
// Vari�veis de movimenta��o da c�mera
double panX_WarmachineKiwi = 0;
double panY_WarmachineKiwi = 0;

// Vari�veis que operam no rob� como um todo
double pX_WarmachineKiwi = 0.0, pY_WarmachineKiwi = 0.0, pZ_WarmachineKiwi = 0.0; // Posi��o e transla��o
double rX_WarmachineKiwi = 0.0, rY_WarmachineKiwi = 0.0, rZ_WarmachineKiwi = 0.0; // Rota��o
double sX_WarmachineKiwi = 1.0, sY_WarmachineKiwi = 1.0, sZ_WarmachineKiwi = 1.0; // Escala
double animVelocity_WarmachineKiwi = 2.58; // Velocidade de anima��o

// Vari�veis que operam em partes espec�ficas do rob�
// Perna Esquerda
int stateLeftLegPendulum_WarmachineKiwi = 1; // 0 = Perna balan�a para frente; 1 = Perna balan�a para tr�s; -1 = fica parado
double rLeftLegFirst_WarmachineKiwi = 0.0; // Primeiro parte m�vel de cima para baixo
double rLeftLegSecond_WarmachineKiwi = 0.0; // Segundo parte m�vel de cima para baixo
double rLeftLegThird_WarmachineKiwi = 0.0; // Terceiro parte m�vel de cima para baixo
double rLeftLegFourth_WarmachineKiwi = 0.0; // Quarta parte m�vel de cima para baixo (p�)

// Perna Direita
int stateRightLegPendulum_WarmachineKiwi = 0; // 0 = Perna balan�a para frente; 1 = Perna balan�a para tr�s; -1 = fica parado
double rRightLegFirst_WarmachineKiwi = 0.0; // Primeiro parte m�vel de cima para baixo
double rRightLegSecond_WarmachineKiwi = 0.0; // Segundo parte m�vel de cima para baixo
double rRightLegThird_WarmachineKiwi = 0.0; // Terceiro parte m�vel de cima para baixo
double rRightLegFourth_WarmachineKiwi = 0.0; // Quarta parte m�vel de cima para baixo (p�)


//============================================//
//              C�MERA DO ROB�
//============================================//

void isometricCamera_WarmachineKiwi(float fAspect){ // C�mera isom�trica - Visualiza��o t�tica
    // Troca o modo da matriz para ajustar a c�mera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define a c�mera como ortogonal
    glOrtho(-10.0f*fAspect - panX_WarmachineKiwi, 10.0f*fAspect - panX_WarmachineKiwi, -10.0f*fAspect - panY_WarmachineKiwi, 10.0f*fAspect - panY_WarmachineKiwi, -60.0f*fAspect, 60.0f*fAspect);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotaciona nos eixos para que a angula��o isom�trica fique correta
    glRotatef(35.264f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
}
void perspectiveCamera_WarmachineKiwi(float fAspect){ // C�mera perspectiva - Visualiza��o de comando
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Cria a c�mera em perspectiva
    gluPerspective(60.0, fAspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Posiciona a c�mera acima no rob�
    gluLookAt(pX_WarmachineKiwi + 2*cos((PI/180)*(rY_WarmachineKiwi - 90)),
              pY_WarmachineKiwi + 0.65,
              pZ_WarmachineKiwi - 2*sin((PI/180)*(rY_WarmachineKiwi - 90)),

              pX_WarmachineKiwi,
              pY_WarmachineKiwi,
              pZ_WarmachineKiwi,

              0,1,0);
}


//============================================//
//              ANIMA��O DO ROB�
//============================================//
void resetFlags_WarmachineKiwi(){ // Reseta as flags de anima��o
    stateLeftLegPendulum_WarmachineKiwi = 1; // 0 = Perna balan�a para frente; 1 = Perna balan�a para tr�s; -1 = fica parado
    rLeftLegFirst_WarmachineKiwi = 0.0; // Primeiro parte m�vel de cima para baixo
    rLeftLegSecond_WarmachineKiwi = 0.0; // Segundo parte m�vel de cima para baixo
    rLeftLegThird_WarmachineKiwi = 0.0; // Terceiro parte m�vel de cima para baixo
    rLeftLegFourth_WarmachineKiwi = 0.0; // Quarta parte m�vel de cima para baixo (p�)

    // Perna Direita
    stateRightLegPendulum_WarmachineKiwi = 0; // 0 = Perna balan�a para frente; 1 = Perna balan�a para tr�s; -1 = fica parado
    rRightLegFirst_WarmachineKiwi = 0.0; // Primeiro parte m�vel de cima para baixo
    rRightLegSecond_WarmachineKiwi = 0.0; // Segundo parte m�vel de cima para baixo
    rRightLegThird_WarmachineKiwi = 0.0; // Terceiro parte m�vel de cima para baixo
    rRightLegFourth_WarmachineKiwi = 0.0; // Quarta parte m�vel de cima para baixo (p�)
}
void walkLeftLeg_WarmachineKiwi(){// Anima a perna esquerda
    if(stateLeftLegPendulum_WarmachineKiwi == 0){
        // Primeiro peda�o da perna
        if(rLeftLegFirst_WarmachineKiwi < 30){
            rLeftLegFirst_WarmachineKiwi = rLeftLegFirst_WarmachineKiwi + animVelocity_WarmachineKiwi;

            // Segundo peda�o da perna
            if(rLeftLegFirst_WarmachineKiwi >= 0) rLeftLegSecond_WarmachineKiwi = rLeftLegSecond_WarmachineKiwi + animVelocity_WarmachineKiwi;
            else rLeftLegSecond_WarmachineKiwi = rLeftLegSecond_WarmachineKiwi - animVelocity_WarmachineKiwi;

            // Terceiro peda�o da perna
            if(rLeftLegFirst_WarmachineKiwi >= 0) rLeftLegThird_WarmachineKiwi = rLeftLegThird_WarmachineKiwi - animVelocity_WarmachineKiwi;
            else rLeftLegThird_WarmachineKiwi = rLeftLegThird_WarmachineKiwi + animVelocity_WarmachineKiwi;

            // Quarto peda�o da perna (p�)
            rLeftLegFourth_WarmachineKiwi = rLeftLegFourth_WarmachineKiwi - animVelocity_WarmachineKiwi;
        }

        else stateLeftLegPendulum_WarmachineKiwi = 1;
    }
    else if(stateLeftLegPendulum_WarmachineKiwi == 1){
        if(rLeftLegFirst_WarmachineKiwi > -30){
            rLeftLegFirst_WarmachineKiwi = rLeftLegFirst_WarmachineKiwi - animVelocity_WarmachineKiwi;

            // Segundo peda�o da perna
            if(rLeftLegFirst_WarmachineKiwi >= 0) rLeftLegSecond_WarmachineKiwi = rLeftLegSecond_WarmachineKiwi - animVelocity_WarmachineKiwi;
            else rLeftLegSecond_WarmachineKiwi = rLeftLegSecond_WarmachineKiwi + animVelocity_WarmachineKiwi;

            // Terceiro peda�o da perna
            if(rLeftLegFirst_WarmachineKiwi >= 0) rLeftLegThird_WarmachineKiwi = rLeftLegThird_WarmachineKiwi + animVelocity_WarmachineKiwi;
            else rLeftLegThird_WarmachineKiwi = rLeftLegThird_WarmachineKiwi - animVelocity_WarmachineKiwi;

            // Quarto peda�o da perna (p�)
            rLeftLegFourth_WarmachineKiwi = rLeftLegFourth_WarmachineKiwi + animVelocity_WarmachineKiwi;
        }
        else stateLeftLegPendulum_WarmachineKiwi = 0;
    }

    glutPostRedisplay();
}
void walkRightLeg_WarmachineKiwi(){// Anima a perna direita
    if(stateRightLegPendulum_WarmachineKiwi == 0){
        // Primeiro peda�o da perna
        if(rRightLegFirst_WarmachineKiwi < 30){
            rRightLegFirst_WarmachineKiwi = rRightLegFirst_WarmachineKiwi + animVelocity_WarmachineKiwi;

            // Segundo peda�o da perna
            if(rRightLegFirst_WarmachineKiwi >= 0) rRightLegSecond_WarmachineKiwi = rRightLegSecond_WarmachineKiwi + animVelocity_WarmachineKiwi;
            else rRightLegSecond_WarmachineKiwi = rRightLegSecond_WarmachineKiwi - animVelocity_WarmachineKiwi;

            // Terceiro peda�o da perna
            if(rRightLegFirst_WarmachineKiwi >= 0) rRightLegThird_WarmachineKiwi = rRightLegThird_WarmachineKiwi - animVelocity_WarmachineKiwi;
            else rRightLegThird_WarmachineKiwi = rRightLegThird_WarmachineKiwi + animVelocity_WarmachineKiwi;

            // Quarto peda�o da perna (p�)
            rRightLegFourth_WarmachineKiwi = rRightLegFourth_WarmachineKiwi - animVelocity_WarmachineKiwi;
        }

        else stateRightLegPendulum_WarmachineKiwi = 1;
    }
    else if(stateRightLegPendulum_WarmachineKiwi == 1){
        if(rRightLegFirst_WarmachineKiwi > -30){
            rRightLegFirst_WarmachineKiwi = rRightLegFirst_WarmachineKiwi - animVelocity_WarmachineKiwi;

            // Segundo peda�o da perna
            if(rRightLegFirst_WarmachineKiwi >= 0) rRightLegSecond_WarmachineKiwi = rRightLegSecond_WarmachineKiwi - animVelocity_WarmachineKiwi;
            else rRightLegSecond_WarmachineKiwi = rRightLegSecond_WarmachineKiwi + animVelocity_WarmachineKiwi;

            // Terceiro peda�o da perna
            if(rRightLegFirst_WarmachineKiwi >= 0) rRightLegThird_WarmachineKiwi = rRightLegThird_WarmachineKiwi + animVelocity_WarmachineKiwi;
            else rRightLegThird_WarmachineKiwi = rRightLegThird_WarmachineKiwi - animVelocity_WarmachineKiwi;

            // Quarto peda�o da perna (p�)
            rRightLegFourth_WarmachineKiwi = rRightLegFourth_WarmachineKiwi + animVelocity_WarmachineKiwi;
        }
        else stateRightLegPendulum_WarmachineKiwi = 0;
    }

    glutPostRedisplay();
}
// Anima as duas pernas
void walk_WarmachineKiwi(){
    walkLeftLeg_WarmachineKiwi();
    walkRightLeg_WarmachineKiwi();
}


//============================================//
//              TEXTURAS DO ROB�
//============================================//
void loadTextures_WarmachineKiwi(){

    // Perna
    CarregaTextura("foot_WarmachineKiwi.bmp", FOOT_WARMACHINEKIWI);

    // Corpo
    CarregaTextura("face_WarmachineKiwi.bmp", FACE_WARMACHINEKIWI);
    CarregaTextura("emblem_WarmachineKiwi.bmp", EMBLEM_WARMACHINEKIWI);

    // Arma
    CarregaTextura("gunFront_WarmachineKiwi.bmp", GUNFRONT_WARMACHINEKIWI);
    CarregaTextura("gunFace_WarmachineKiwi.bmp", GUNFACE_WARMACHINEKIWI);
}


//============================================//
//              MODELAGEM DO ROB�
//============================================//
void base_WarmachineKiwi(){ // Base do rob�
    glColor3d(0.168, 0.25, 0.36);

    // Base de liga��o entre as pernas e o corpo
    glPushMatrix();
        glScaled(0.75, 0.25, 0.25);
        glutSolidCube(0.6);
    glPopMatrix();

    // Liga��o base da perna e o corpo
    glPushMatrix();
        glTranslated(0.0, 0.1, -0.1);
        glScaled(0.25, 1.0, 0.5);
        glutSolidCube(0.4);
    glPopMatrix();

    // Corpo
    glPushMatrix();
        // Quad para textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId_WarmachineKiwi[FACE_WARMACHINEKIWI]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.15f, 0.42f, -0.242f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(0.15f, 0.42f, -0.242f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15f, 0.1f, -0.242f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.15f, 0.1f, -0.242f);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glTranslated(0.0, 0.26, 0.02);
        glScaled(0.75, 0.8, 1.3);
        glutSolidCube(0.4);
    glPopMatrix();

    glColor3d(0.647, 0.702, 0.761);
    // Placa da frente
    glPushMatrix();
        // Quad para textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId_WarmachineKiwi[EMBLEM_WARMACHINEKIWI]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.14f, 0.04f, -0.222f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(0.14f, 0.04f, -0.222f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(0.14f, -0.44f, -0.222f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.14f, -0.44f, -0.222f);

            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.14f, 0.04f, -0.196f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(0.14f, 0.04f, -0.196f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(0.14f, -0.44f, -0.196f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.14f, -0.44f, -0.196f);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glTranslated(0.0, -0.2, -0.21);
        glScaled(0.7, 1.2, 0.05);
        glutSolidCube(0.4);
    glPopMatrix();
}
void leftLeg_WarmachineKiwi(){ // Perna esquerda
    glColor3d(0.15, 0.15, 0.15);

    glTranslated(-0.25, -0.0375, -0.05);
    // Rota��o da perna toda
    glRotated(rLeftLegFirst_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o giro ficar certo
    glTranslated(0, -0.0625, 0);

    // Primeira parte da perna

    glPushMatrix();
        glRotated(20.0, 1.0 ,0.0, 0.0);
        glScaled(0.1, 0.5, 0.25);
        glutSolidCube(0.5);
    glPopMatrix();

    // Junta da perna entre partes 1 e 2
    glPushMatrix();
        glTranslated(-0.01, -0.1, -0.1);
        glScaled(0.75, 1.4, 1.0);
        glutSolidCube(0.15);
    glPopMatrix();

    // Arruma a posi��o
    glTranslated(0, -0.0625, -0.085);
    // Rota��o das partes da perna que est�o abaixo
    glRotated(rLeftLegSecond_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o giro ficar certo
    glTranslated(0, 0.0625, 0.085);

    // Segunda parte da perna
    glPushMatrix();
        glTranslated(0.0, -0.10, 0.07);
        glScaled(0.12, 0.25, 0.6);
        glutSolidCube(0.5);
    glPopMatrix();

    // Arruma a posi��o
    glTranslated(0.0 ,-0.0875 , 0.18);
    // Rota��o das partes da perna que est�o abaixo
    glRotated(rLeftLegThird_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o eixo de giro ficar certo
    glTranslated(0.0, -0.2915, -0.0725);
    glTranslated(0.0 ,0.32 , -0.15);

    // Terceira parte da perna
    glPushMatrix();
        glTranslated(0.0 ,-0.32 , 0.15);
        glRotated(10.0, 1.0 ,0.0, 0.0);
        glScaled(0.12, 1.25, 0.25);
        glutSolidCube(0.5);
    glPopMatrix();


    // Arruma a posi��o
    glTranslated(0.0 ,-0.62, 0.06);
    // Rota��o das partes da perna que est�o abaixo
    glRotated(rLeftLegFourth_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o eixo de giro ficar certo
    glTranslated(0.0 ,0.62, -0.06);

    // P�
    glPushMatrix();
      glTranslated(0.0 ,-0.62, 0.06);
      glScaled(0.08, 0.08, 0.16);

      glEnable(GL_TEXTURE_2D);
      glBindTexture (GL_TEXTURE_2D, textureId_WarmachineKiwi[FOOT_WARMACHINEKIWI]);
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
void rightLeg_WarmachineKiwi(){ // Perna direita
    glColor3d(0.15, 0.15, 0.15);

    glTranslated(0.25, -0.0375, -0.05);
    // Rota��o da perna toda
    glRotated(rRightLegFirst_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o giro ficar certo
    glTranslated(0, -0.0625, 0);

    // Primeira parte da perna
    glPushMatrix();
        glRotated(20.0, 1.0 ,0.0, 0.0);
        glScaled(0.1, 0.5, 0.25);
        glutSolidCube(0.5);
    glPopMatrix();

    // Junta da perna entre partes 1 e 2
    glPushMatrix();
        glTranslated(0.01, -0.1, -0.1);
        glScaled(0.75, 1.4, 1.0);
        glutSolidCube(0.15);
    glPopMatrix();

    // Arruma a posi��o
    glTranslated(0, -0.0625, -0.085);
    // Rota��o das partes da perna que est�o abaixo
    glRotated(rRightLegSecond_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o giro ficar certo
    glTranslated(0, 0.0625, 0.085);

    // Segunda parte da perna
    glPushMatrix();
        glTranslated(0.0, -0.10, 0.07);
        glScaled(0.12, 0.25, 0.6);
        glutSolidCube(0.5);
    glPopMatrix();

    // Arruma a posi��o
    glTranslated(0.0 ,-0.0875 , 0.18);
    // Rota��o das partes da perna que est�o abaixo
    glRotated(rRightLegThird_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o eixo de giro ficar certo
    glTranslated(0.0, -0.2915, -0.0725);
    glTranslated(0.0 ,0.32 , -0.15);

    // Terceira parte da perna
    glPushMatrix();
        glTranslated(0.0 ,-0.32 , 0.15);
        glRotated(10.0, 1.0 ,0.0, 0.0);
        glScaled(0.12, 1.25, 0.25);
        glutSolidCube(0.5);
    glPopMatrix();


    // Arruma a posi��o
    glTranslated(0.0 ,-0.62, 0.06);
    // Rota��o das partes da perna que est�o abaixo
    glRotated(rRightLegFourth_WarmachineKiwi, 1.0, 0.0, 0.0);
    // Deslocamento para o eixo de giro ficar certo
    glTranslated(0.0 ,0.62, -0.06);

    // P�
    glPushMatrix();
      glTranslated(0.0 ,-0.62, 0.06);
      glScaled(0.08, 0.08, 0.16);

      glEnable(GL_TEXTURE_2D);
      glBindTexture (GL_TEXTURE_2D, textureId_WarmachineKiwi[FOOT_WARMACHINEKIWI]);
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
void gun_WarmachineKiwi(){ // Arma
    glColor3d(1.0, 1.0, 1.0);

    glPushMatrix();
        glTranslated(0.0, 0.25, -0.8);
        // Frente
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId_WarmachineKiwi[GUNFRONT_WARMACHINEKIWI]);
        glBegin(GL_TRIANGLES);
          glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 0.05f, 0.0f);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.05f, -0.05f, 0.0f);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(0.05f, -0.05f, 0.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        // Faces
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId_WarmachineKiwi[GUNFACE_WARMACHINEKIWI]);
        glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.05f, 0.0f);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.05f, 0.7f);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(0.05f, -0.05f, 0.7f);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(0.05f, -0.05f, 0.0f);

          glTexCoord2f(0.0f, 1.0f); glVertex3f(0.05f, -0.05f, 0.0f);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(0.05f, -0.05f, 0.7f);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.05f, -0.05f, 0.7f);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.05f, -0.05f, 0.0f);

          glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.05f, 0.0f);
          glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.05f, 0.7f);
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.05f, -0.05f, 0.7f);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.05f, -0.05f, 0.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
// Desenha todas as pe�as do rob� juntas
void draw_WarmachineKiwi(){

    // Movimenta��o do rob�
    glTranslated(pX_WarmachineKiwi, pY_WarmachineKiwi, pZ_WarmachineKiwi);
    // Rota��o do rob� nos seus eixos
    glRotated(rX_WarmachineKiwi, 1.0, 0.0, 0.0);
    glRotated(rY_WarmachineKiwi, 0.0, 1.0, 0.0);
    glRotated(rZ_WarmachineKiwi, 0.0, 0.0, 1.0);
    // Escala do rob�
    glScaled(sX_WarmachineKiwi, sY_WarmachineKiwi, sZ_WarmachineKiwi);

    // Desenha as partes do rob�
    glPushMatrix();
        base_WarmachineKiwi();
    glPopMatrix();

    glPushMatrix();
        leftLeg_WarmachineKiwi();
    glPopMatrix();

    glPushMatrix();
        rightLeg_WarmachineKiwi();
    glPopMatrix();

    glPushMatrix();
        gun_WarmachineKiwi();
    glPopMatrix();
}

//============================================//
//           MOVIMENTA��O DO ROB�
//============================================//
void moveFoward_WarmachineKiwi(){
    if(pZ_WarmachineKiwi >= -50 && pZ_WarmachineKiwi <= 50) pZ_WarmachineKiwi -= 0.28*cos((PI/180)*rY_WarmachineKiwi);
    else pZ_WarmachineKiwi += 0.28*cos((PI/180)*rY_WarmachineKiwi);
    if(pX_WarmachineKiwi >= -50 && pX_WarmachineKiwi <= 50) pX_WarmachineKiwi -= 0.28*sin((PI/180)*rY_WarmachineKiwi);
    else pX_WarmachineKiwi += 0.28*sin((PI/180)*rY_WarmachineKiwi);
}
void moveBackward_WarmachineKiwi(){
    if(pZ_WarmachineKiwi >= -50 && pZ_WarmachineKiwi <= 50) pZ_WarmachineKiwi += 0.28*cos((PI/180)*rY_WarmachineKiwi);
    else pZ_WarmachineKiwi -= 0.28*cos((PI/180)*rY_WarmachineKiwi);
    if(pX_WarmachineKiwi >= -50 && pX_WarmachineKiwi <= 50) pX_WarmachineKiwi += 0.28*sin((PI/180)*rY_WarmachineKiwi);
    else pX_WarmachineKiwi -= 0.28*sin((PI/180)*rY_WarmachineKiwi);
}
void turnRight_WarmachineKiwi(){
    rY_WarmachineKiwi -= 2.0;
}
void turnLeft_WarmachineKiwi(){
    rY_WarmachineKiwi += 2.0;
}

