// 선을 그리는 브레젠험 알고리즘
// 이 알고리즘의 규칙을 파악하면 8분면의 모든 영역에 선을 자유롭게 그릴 수 있는 알고리즘을 완성할 수 있다.

void WindowsRSI::DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor) {
    /*
        시작점과 끝점이 화면 영역을 벗어나는 경우 클리핑 알고리즘을 수행한다.
        관련 내용은 라인 클리핑 알고리즘이다.
    */
    Vector2 clippedStart = InStartPos;
    Vector2 clippedEnd = InEndPos;
    Vector2 screenExtend = Vector2(_ScreenSize.X, _ScreenSize.Y) * 0.5f;
    Vector2 minScreen = -screenExtend;
    Vector2 maxScreen = screenExtend;
    if(!CohenSutherlanddLineClip(clippedStart, clippedEnd, minScreen, maxScreen))
    {
        return;
    }

    // 시작점을 스크린 좌표계로 변환하고 변수 startPosition에 저장한다.
    ScreendPoint startPosition = ScreenPoint::ToScreenCoordinate(_ScreenSize, clippedStart);
    // 끝 점을 스크린 좌표계로 변환하고 변수 endPostion에 저장한다.
    ScreenPoint endPosition = ScreenPoint::ToScreenCoordinate(_ScreenSize, clippedEnd);

    // endPosition의 X값에서 startPosition의 X값을 뺴 너비를 구하고 변수 width에 저장한다.
    int width = endPosition.X - startPosition.X;
    // endPosition의 Y값에서 startPosition의 Y값을 빼 높이를 구하고 변수 height에 저장한다.
    int height = endPosition.Y - startPosition.Y;

    // 너비와 높이의 절대값을 구한 후 이를 비교해 완만한 경사인지
    // 급격한 경사인지 파악한 후 변수 isGradualSlope에 저장한다.
    bool isGradualSlope = (Math::Abs(width) >= Math::Abs(height));
    // x축 진행 방향이 양수인지 음수인지 판단하고 이를 변수 dx에 저장한다.
    int dx = (width >= 0) ? 1 : -1;
    // Y축 진행 방향이 양수인지 음수인지 판단하고 이를 변수 dy에 저장한다.
    int dy = (height > 0) ? 1 : -1;
    // 변수 dx와 선의 너비를 곱한 값을 변수 fw에 저장한다. (판별식에 쓰인다.)
    int fw = dx * width;
    // 변수 dy와 선의 높이를 곱한 값을 션수 fh에 저장한다. (판별식에 쓰인다.)
    int fh = dy * height;

    // isGrdualSlope 값에 따라 최초 사용할 판별식 f를 지정한다.
    int f = isGradualSlope ? fh * 2 - fw : 2 * fw - fh;
    // 선이 변화없이 진행되는 경우에 사용할 판별식의 조정값을 
    // isGradualSlope 값에 따라 구하고 이를 f2에 저장한다.
    int f1 = isGradualSlope ? 2 * fh : 2 * fw;
    // 선의 진행에 변화가 생기는 경우에 사용할 판별식의 조정값을
    // isGradualSlope 값에 따라 구하고 이를 f2에 저장한다.
    int f2 = isGradualSlope ? 2 * (fh - fw) : 2 * (fw - fh);
    
    // 최초 선 그리기를 시작할 지점을 변수 x와 y에 각각 보관한다.
    int x = startPosition.X;
    int y = startPosition.Y;

    // isGradualSlope 값에 따라 로직을 분기한다.
    // 해당 값이 참이면 1, 4, 5, 8팔분면의 선 그리기가 진행된다.
    if (isGradualSlope) {
        // 끝 점에 도달할 때까지 로직을 계속 반복한다.
        while (x != endPosition.X) {
            // 지정된 색상을 ㅗ해당 스크린 좌표에 점을 찍는다.
            SetPixel(ScreenPoint(x, y), InColor);

            // 판별식이 0보다 작으면 f1 값을 사용해 판별식을 갱신한다.
            if(f < 0) {
                f += f1;
            }

            // 판별식이 0보다 크거나같으면 f2 값을 사용해 판별식을 갱신한다.
            else {
                f += f2;
                // 판별식이 0보다 크거나 같은 상황에서는 y축 값은 한 칸 진행되어야 한다.
                y+= dy;
            }

            // 다음 픽셀로 이동한다.
            x += dx;
        }
    }
    
    // isGradualSlope 값이 거짓이면 2, 3, 6, 7 팔분면의  선 그리기를 진행한다.
    // 해당 로직은 위의 if 문의 진행과 동일하며 단지 x와 y값이 뒤바뀌었을 뿐이다.
    else {
        while (y != endPosition.Y) {
            SetPixel(ScreenPoint(x, y), InColor);

            if (f < 0) {
                f += f1;
            }
            else {
                f += f2;
                x += dx;
            }

            y += dy;
        }
    }

}