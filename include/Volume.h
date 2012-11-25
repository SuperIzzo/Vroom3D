#ifndef __VOLUME_H__
#define __VOLUME_H__



class Volume
{
public:
	unsigned char* data;

	Volume();
	~Volume();

	void LoadFromXZImage( const char * img, int width );
};



#endif