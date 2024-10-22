# Platformer

## WIN32 API 기반 플랫포머 게임
## 사용 언어 : C++
## 의존 라이브러리
  Windows Api, Gdiplus

## MAIN ENTRY
Platformer.cpp
Game.cpp

Scene ----- Init   : 리소스 로드, 액터 배치
        |
        |-- Update : 프레임 단위로 업데이트 ( 35ms 고정 프레임 )
        |
        |-- Render : 화면에 그리기
