# Platformer

## WIN32 API 기반 플랫포머 게임

## 진입점
Platformer.cpp   
Game.cpp

### Scene    
        |-- Init   : 리소스 로드, 액터 배치   
        |   
        |-- Update : 프레임 단위로 업데이트 ( 35ms 고정 프레임 )   
        |   
        |-- Render : 화면에 그리기   

### Service    
입력 처리, 카메라, 충돌 처리, 타이머, 리소스 로더, 타일 맵   

