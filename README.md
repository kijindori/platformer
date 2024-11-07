### [진입점]
Platformer.cpp   -> Game.cpp -> Scene.cpp   

### Scene    
        |-- Init   : 리소스 로드, 액터 배치   
        |   
        |-- Update : 프레임 단위로 업데이트 
        |   
        |-- Render : 화면에 그리기   

### Service    
입력 처리 : InputHandler.cpp   
카메라 : Camera.cpp   
충돌 처리 : Collision.cpp   
타이머 : Timer.cpp   
리소스 로더 : Loader.cpp   
타일 맵  : TilemapService.cpp   
