픽셀좌표는 x,y 좌표로 표현하면 왼쪽위가 (0,0)이고 오른쪽으로 (1,0) 아래로 (0,1) 입니다.
실제 색상데이터는 [(y * width + x) * 4 + ~~~] 에 저장되있음에 유의해야합니다.
변수 중 i, j를 사용하는 함수도 있는데, i는 y좌표, j는 x좌표입니다.

사용 가능한 기능:
사각형 그리기 (O(wh))
원 그리기 (O(r^2))
다이아몬드 그리기 (O(r^2))
직선 그리기 (O(이미지 전체))
다른 이미지 그리기 (O(max(w1h1, w2h2)))


이미지 입/출력 레퍼런스 : https://github.com/nothings/stb

Inital Commit : 2020-03-16 pichulia
Publish github : 2021-06-08 pichulia