#include "resourse.h"
#include "messages.h"
#include "global.h"
#include "game.h"

static unsigned char* loadBitmap(char *file_name,BITMAPINFOHEADER *bitmap_info_header){
	FILE *file_ptr;
	BITMAPFILEHEADER bitmap_file_header;
	fopen_s(&file_ptr,file_name,"rb");
	if(!file_ptr)error("loadBitmap: %s failed to open",file_name);
	fread(&bitmap_file_header,sizeof(BITMAPFILEHEADER),1,file_ptr);
	if(bitmap_file_header.bfType!=0x4D42)error("loadBitmap: %s is not a bitmap file",file_name);

	fread(bitmap_info_header,sizeof(BITMAPINFOHEADER),1,file_ptr);
	fseek(file_ptr,bitmap_file_header.bfOffBits,SEEK_SET);
	unsigned char *bitmap_image=malloc(bitmap_info_header->biSizeImage);
	if(!bitmap_image)error("loadBitmap: memory error");
	fread(bitmap_image,1,bitmap_info_header->biSizeImage,file_ptr);

	unsigned int i;
	for(i=0;i < (bitmap_info_header->biSizeImage);i+=3){
		unsigned char t=bitmap_image[i];
		bitmap_image[i]=bitmap_image[i+2];
		bitmap_image[i+2]=t;
	}
	fclose(file_ptr);
	return bitmap_image;
}

static int loadTexture(char *file_name,int id){
	unsigned char *bitmap_image;
	BITMAPINFOHEADER bitmap_info_header;
	bitmap_image=loadBitmap(file_name,&bitmap_info_header);
	if(!bitmap_image)error("Failed to Load Texture");
	glGenTextures(1,&texture[id]);
	glBindTexture(GL_TEXTURE_2D, texture[id]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	int width=bitmap_info_header.biWidth;
	int height=bitmap_info_header.biHeight;
	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,width,height,GL_RGB,GL_UNSIGNED_BYTE,bitmap_image);
	free(bitmap_image);
	return 1;
}

static int loadMap(MAP *course){
	BITMAPINFOHEADER bitmap_info_header;
	unsigned char *bitmap_image=loadBitmap("data\\map.bmp",&bitmap_info_header);
  
	course->width=bitmap_info_header.biWidth;
	course->height=bitmap_info_header.biHeight;

	course->y=malloc(sizeof(float)*course->width*(course->height-1));
	if(!course->y)
		error("Height malloc() Failed");
	int i;
	for(i=0;i<(course->height-1)*course->width;i++){
		int x=i%course->width;
		int y=i/course->width;
		unsigned char *ptr=bitmap_image+(y*course->width+x)*3;
		int z=ptr[0]|ptr[1]<<8|ptr[2]<<16;
		course->y[i]=YSCALE*(float)z/((1<<24)-1);
	}
	free(bitmap_image);
	return 1;
}

void loadResourse(){
	loadTexture("data\\ship.bmp",8);
	loadTexture("data\\lf.bmp",2);
	loadTexture("data\\rt.bmp",3);
	loadTexture("data\\dn.bmp",4);
	loadTexture("data\\up.bmp",5);
	loadTexture("data\\ft.bmp",6);
	loadTexture("data\\bk.bmp",7);
	loadTexture("data\\terrain.bmp",9);
	loadTexture("data\\map.bmp",13);
	loadMap(&map);
}

