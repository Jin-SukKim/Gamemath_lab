// 코헨-서덜랜드 라이 클리핑 알고맂므(Cohen_Sutherland line clipping algorithm)
/*
    브레젠험 알고리즘은 단순하고 빠른 알고리즘이지만 이것만으로 선을 그리기에는 충분하지 않다.
    한 픽셀식 전진하면서 점을 찍기에 화면을 벗어나는 큰 값이 들어오더라도
    목표에 도달할 때까지 모두 계산해야 한다.

    긴 선분이 들어왔을 떄 화면 영영ㄱ에 유효한 선분으로 잘라주는 알고리즘으로 이를 방지해 준다.

    이렇게 선분이 가진 성질은 유지하며 지정된 여역에 맞는 데이터로 재설정하는 작업을 클리핑(Clipping)이라고 한다.
*/
/*
    선분 그릴 때를 고려해야 할 상황
    1. 화면 안에 위치해서 자를 필요가 없는 경우
    2. 화면 밖에 위치해 있어서 그릴 필요가 없는 경우
    3. 화면을 가로질러서 화면에 유효한 영역으로 잘라내야 하는 경우
*/

// 주어진 점의 영역 값을 돌려주는 로직
int TestRegion(const Vector2 &InVectorPos, const Vector2 &InMinPos, const Vector2 &InMaxPos)
{
    // 테스트 결과에 사용하는 변수 result를 선언하고 값을 0으로 지정
    int result = 0;

    // 입력된 벡터의 X값이 최솟값보다 작으면 하위 2비트에 01을 지정한다.
    if (InVectorPos.X < InMinPos.X)
    {
        result = result | 0b0001;
    }
    // 입력된 벡터의 X값이 최댓값보다 크면 하위 2비트에 10을 지정한다.
    else if (InVectorPos.X > InMaxPos.X)
    {
        result = result | 0b0010;
    }

    // 입력된 벡터의 Y값이 최솟값보다 작으면 상위 2비트에 01을 지정한다.
    if (InVectorPos.Y < InMinPos.Y)
    {
        result = result | 0b0100;
    }
    // 입력된 벡터의 Y값이 최댓값보다 크면 상위 2비트에 10을 지정한다.
    else if (InVectorPos.Y > InMaxPos.Y)
    {
        result = result | 0b1000;
    }

    // 최종값
    return result;
}

// 코헨 서덜랜드 직선 클리핑 알고리즘ㅇ르 구현한 함수
bool CohenSutherlandLineClip(Vector2& InOutStartPos, Vector2& InOutEndPos,
                                const Vector2& InMinPos, const Vector2& InMaxPos)
{
    // 첫 번째 점의 영역 테스트 결과를 변수 startTest에 저장ㅎ나다.
    int startTest = TestRegion(InOutStartPos, InMinPos, InMaxPos);
    // 두 번째 점의 영역 테스트 결과를 변수 endTest에 저장한다.
    int endTest = TestRegion(InOutEndPos, InMinPos, InMaxPos);

    // 선분의 너비를 구하고 변수 width에 저장한다.
    float width = (InOutEndPos.X - InOutStartPos.X);
    // 선분의 높이를 구하고 변수 heigth에 저장한다.
    float height = (InOutEndPos.Y - InOutStartPos.Y);

    // 루프 종료할 때까지 반복한다.
    while(true) {
        // 두 테스트 결과가 모두 0이면 화면 안에 선분이 위치ㅐ 있다는 의미이므로 바로 true를 반환하다.
        if ((startTest == 0) && (endTest == 0)) { // 화면 안에 두 점이 있으면 바로 그리기
            return true;
        }
        // 두 테스트 결과를 & 연산시켰을 때 0이 아니라면 두점은 그릴 필요가 없다. 바로 false를 반환하다.
        else if (startTest & endTest) { // 화면 밖에 선이 있으므로 그릴 필요가 없음
            return false;
        }
        // 두 테스트 결과가 0이면 직선의 방정식을 사용해 각 점의 클리핑 작업을 진행한다.
        else { // 양쪽을 조사해 클리핑 진행

        }
    }
}

void DrawLine(const Vector2& InStartPos, const Vector2& InEndPos, const LinearColor& InColor) {
    // 시작점과 끝점정보를 각각 변수 clippedStart, clippedEnd에 저장ㅎ나다.
    Vector2 clippedStart = InStartPos;
    Vector2 ClippedEnd = InEndPos;

    // 화면 크기의 절반 ㄱ밧을 변수 screendExtend에 저장한다.
    Vector2 screenExtend = Vector2(_ScreenSize.X, _ScreendSize.Y) * 0.5f;
    
    // screendExtend 값을 사용해 화면으 ㅣ최솟값과 최댁밧을 구한다.
    Vector2 minScreen = _screenExtend;
    Vector2 maxScreen = screenExtend;

    // 클리핑 결과를 확인한다.
    // false가 나오면 함수도 바로 종료한다.
    if(!CohenSutherlandLineClip(clippedStart, clippedEnd, minScreen, maxScreen)) {
        return;
    }
}