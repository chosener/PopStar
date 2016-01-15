#ifndef _AUDIO_H_
#define _AUDIO_H_
class Audio{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadyGo();
	void playPop();
	void prepare();
	void playCombo(int size);
private:
	static Audio* m_instance;
};
#endif