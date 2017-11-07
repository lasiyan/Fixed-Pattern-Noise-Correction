# Edge-Detection-Application

This Application aim to detect the lines using Sobel or my custom Algorithm. In image processing, this app associated with Edge Detection and Fixed pattern Noise.

해당 애플리케이션은 Bitmap 이미지에 발생한 Fixed Pattern Noise를 검출하기 위한 애플리케이션이다. 해당 애플리케이션은 MFC 기반 프로젝트로 구성되었으며, 발생한 노이즈를 Vertical Sobel Detection 알고리즘 또는 직접 구현한 Custom Alogrithm을 통해 검출하며 탐지 결과를 Bitmap 이미지로 저장한다.

## 개발 환경

* OS : Windows 10 Pro 64bit (App: 32bit)
* CPU : Intel(R) Core(TM) i7-6500U CPU @ 2.50GHz 2.59 GHz
* RAM : 8.00GB
* IDE : Microsoft Visual Studio 2008 Version 9.0.30729.1 SP

## 사용 기술

C++, Window API, STL Vector, MFC, Image Processing, Sobel Algorithm, FPN Detection Algorithm

## 부가 설명

먼저 프로그램을 실행하면 하고 노이즈가 발생한 이미지를 불러온다(Bitamp Type). 해당 이미지를 불러오면 이미지에 대한 HBITMAP 객체가 생성되며 CBitmap과 Bitmap 객체를 통해 해당 이미지에 대한 정보(가로, 세로, 픽셀 비트, 컬러 타입 등)가 File Information 에디트 박스에 출력된다. 이후 탐지에 사용할 알고리즘(Sobel, Custom)을 선택 후 Active 버튼을 클릭하면 프로그램이 시작된다.

Active 버튼에 따른 로직은 크게 다음과 같다.
1. 파일의 정보를 기반으로 CMyImage의 객체인 pFile을 생성하고 픽셀 데이터를 저장한다.
2. 이미지의 컬러 타입이 24bit일 경우 8bit Gray Image로 변환한다.
3. 선택한 알고리즘을 통해 노이즈 검사를 실시한다.
4. 검사 결과를 Detect Point 창에 출력하고 검출된 이미지를 저장한다.

픽셀 데이터는 ActiveProcess 클래스의 LoadFile을 통해 수행되며 해당 이미지의 8Bit Grayscale로 변환은 동일 클래스의 Make8BitGray 메서드가 담당한다. 해당 메서드는 CMyImage 객체를 인자로 받아 CMyImage에 구현된 멤버 메서드인 RGBto8BitGray에서 Luma Coding 공식을 통해 변환된다. 

변환이 완료된 이미지는 각각의 알고리즘에 따라 처리되는데 먼저 Sobel의 경우 Sobel Vertical Mask에 따른 수직 방향의 경계를 검출한다. 이는 FPN가 수직 값을 가짐을 가정하며, 정상적인 이미지 패턴에서 수직의 이상(이물) 선분이 발생할 경우 해당 선분을 검출하는 원리이다. 또 다른 알고리즘인 Custom의 경우 가로와 세로의 FPN을 모두 검출 가능하다. 작동 원리는 가로 또는 세로에 포함된 모든 픽셀에 대한 평균 값을 계산하고 해당 값이 임의로 설정한 임계 값(헤더의 THRESHOLD_VAL)과 일정 값만큼 차이가 발생할 경우 이를 Noise로 간주한다.

이렇게 검출된 노이즈의 시작 좌표 값은 글로벌 벡터인 g_cor에 저장되며 검출 알고리즘이 종료된 후 Detect Point 에디트 박스에 좌표 값들을 출력한다. 이후 원본 이미지에서 가시성을 위해 노이즈가 검출되지 않은 부분에 대한 이미지 값을 모두 255(White)로 설정하고 FPN이 검출된 부분에 대해서만 0(Black) 값을 적용하여 저장한다.

## 실행 과정

1. 솔루션 생성 및 Source, Header Files Include
2. 솔루션 빌드 및 실행
3. Bmp 파일 선택 후 검출할 알고리즘 선택
4. Active 버튼을 통한 실행

## 실행 결과

추후 업로드 예정입니다.

(클릭 시 유튜브로 이동합니다)
