# ofxTransmitScreen
oFの画面をofxOSCで送信するaddon（Windouwsのみ動作確認)   
別スレッドで処理してるためメインスレッドには、影響が少ないので
------
##必須Addon
+ ofxOSC 
+ ofxTurboJpeg(https://github.com/robotconscience/ofxTurboJpeg.git)


------
##関数   
------
    void setup(string host,int port);   
+   '送信先のアドレス、ポートを設定する':

------
    void setOptions(int quality);   
+   '出力される画像のクオリティ設定（1～100）' 

------
    void setOptions(int width,int heigh,int quality);  
+   '出力される画像の幅'
+   '出力される画像の高さ'   
+   '出力される画像のクオリティ設定（1～100）'

------
    void get();
+   '画面全体の取得'

------
    void start()
+   '送信開始'

------
    void stop()
+   '送信停止'
------
##サンプル
    //ofApp.h
    #pragma once
  
    #include "ofMain.h"
    #include "ofxTransmitScreen.h"
    class ofApp : public ofBaseApp{
    	public:
    		void setup();
    		void update();
    		void draw();
    		void keyPressed(int key);
    		void keyReleased(int key);
    		void mouseMoved(int x, int y );
    		void mouseDragged(int x, int y, int button);
    		void mousePressed(int x, int y, int button);
    		void mouseReleased(int x, int y, int button);
    		void windowResized(int w, int h);
    		void dragEvent(ofDragInfo dragInfo);
    		void gotMessage(ofMessage msg);
    		void exit();
    
    		ofxTransmitScreen screen; 
    };
------
    //ofApp.cpp
    #include "ofApp.h"
    
    //--------------------------------------------------------------
    void ofApp::setup(){
    	ofBackground(0);
      ofSetFrameRate(60);
    
    	screen.setup("127.0.0.1",8080);　//送信先のホストとポート番号を指定
    	screen.setOptions(512,512,50);   //jpgの設定
    	screen.start();

    }
    
    //--------------------------------------------------------------
    void ofApp::update(){
    	
    }
    
    //--------------------------------------------------------------
    void ofApp::draw(){
    
    	screen.get(); //最後に画面全体を取得
    }
    
    //省略
    
    void ofApp::exit(){
    	screen.stop();
    }
------
##応用
+ [Unity-OSC]でテクスチャとして受信可能

[Unity-OSC]:https://github.com/keijiro/unity-osc
------
##予定
+ 800x800以上になると出力される画像が不安定になる

------
ライセンス
Copyright &copy; 2015 Katsuyoshi Hotta [@Savant_Cat](https://twitter.com/Savant_Cat)  
Licensed under the [MIT license][MIT]
[MIT]: http://www.opensource.org/licenses/mit-license.php
