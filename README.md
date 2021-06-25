픽셀좌표는 x,y 좌표로 표현하면 왼쪽위가 (0,0)이고 오른쪽으로 (1,0) 아래로 (0,1) 입니다.
실제 색상데이터는 (y * width + x) * 4 + ~~~ 에 저장되있음에 유의해야합니다.
변수 중 i, j를 사용하는 함수도 있는데, i는 y좌표, j는 x좌표입니다.

사용 가능한 기능:

* 사각형 그리기 (O(wh))
* 원 그리기 (O(r^2))
* 다이아몬드 그리기 (O(r^2))
* 직선 그리기 (O(이미지 전체))
* 다른 이미지 그리기 (O(max(w1h1, w2h2)))

예제 이미지

<table>
  <tr><td><p align="center"><img src="./sampleImages/sample1.png" alt="sample1"/></p></td><td><p align="center"><img src="./sampleImages/sample2.png" alt="sample2"/></p></td></tr>
  <tr><td><p align="center">Sample 1 : Red gradient                              </p></td><td><p align="center">Sample 2 : Rectangles + Diamond + Circle             </p></td></tr>
  <tr><td><p align="center"><img src="./sampleImages/sample3.png" alt="sample3"/></p></td><td><p align="center"><img src="./sampleImages/sample4.png" alt="sample4"/></p></td></tr>
  <tr><td><p align="center">Sample 3 : Rectangles + Diamond + Circle only border </p></td><td><p align="center">Sample 4 : Lines                                     </p></td></tr>
  <tr><td><p align="center"><img src="./sampleImages/sample5.png" alt="sample5"/></p></td><td><p align="center"><img src="./sampleImages/sample6.png" alt="sample6"/></p></td></tr>
  <tr><td><p align="center">Sample 5 : Alpha blending and Alpha Behavior         </p></td><td><p align="center">Sample 6 : Load Image                                </p></td></tr>
  <tr><td colspan=2><p align="center"><img src="./sampleImages/sample7.png" alt="sample7"/>                                                                          </p></td></tr>
  <tr><td colspan=2><p align="center">Sample 7 : Whatever you want                                                                                                   </p></td></tr>
  <tr><td colspan=2><p align="center"><img src="./sampleImages/sample8.png" alt="sample8"/>                                                                          </p></td></tr>
  <tr><td colspan=2><p align="center">Sample 8 : Resize Image                                                                                                        </p></td></tr>
</table>


이미지 입/출력 레퍼런스 : https://github.com/nothings/stb

Inital Commit : 2020-03-16 pichulia

Publish github : 2021-06-08 pichulia
