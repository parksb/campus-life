# Page Replacement Simulation

Page Replacement 알고리즘을 시뮬레이션하는 프로그램. frame 10개에 reference string 1000개가 접근한다. FIFO, Optimal, LRU Ref Count, LRU Second Chance 총 4가지 알고리즘를 시뮬레이션하며, page fault가 발생하면 event.log 파일에 로그를 남긴다.

각 알고리즘 함수는 page replacement 알고리즘의 핵심 메커니즘을 구현했으며, 가장 먼저 전체 프레임을 순회하며 free frame이나 swap in하려는 페이지와 같은 페이지가 있는지 확인한다. 만약 없다면 page fault가 발생했다고 판단하고 해당 알고리즘이 가진 replacement 작업을 실행한다.

## Uniform Distribution

![uniform dist](https://user-images.githubusercontent.com/6410412/56424538-a82f0080-62eb-11e9-9a9e-f7425faf824d.PNG)

X축은 reference string 값의 범위 0 <= str <= n이며, Y축은 page fault의 발생 횟수를 의미한다. reference string의 범위를 0 <= str <= 50부터 0 <= str <= 1000까지로 설정해 총 20회 테스트했다.

Optimal은 모든 경우에서 page fault 발생 횟수가 가장 낮았다. 다만 실제로는 미래에 사용되지 않을 page를 찾는 데 큰 어려움이 있을 것이며, 시뮬레이션의 경우 매번 reference string을 순회해 빈도가 낮은 page를 찾아야 하므로 시간적 비용을 무시할 수 없을 것으로 보인다.

FIFO와 Second Chance, LRU Reference Count은 모두 비슷한 결과를 보였으며, Second Chance와 LRU Reference Count는 전체 페이지를 순회하는 상황이 발생할 수 있어 FIFO보다 많은 시간과 공간을 요구할 것이라고 생각된다.


## Normal Distribution

![normal dist1](https://user-images.githubusercontent.com/6410412/56424533-9f3e2f00-62eb-11e9-94b2-e124870d57d1.PNG)

![normal dist2](https://user-images.githubusercontent.com/6410412/56424536-a5cca680-62eb-11e9-9dc9-b8d0afdbe8e5.PNG)

normal distribution의 경우 알고리즘별로 보다 큰 차이가 생길 것으로 예상했으나 그 차이는 크지 않았다. LRU Reference Count의 경우 FIFO와 거의 같은 결과값을 냈고, Second Chance는 뚜렷한 일관성을 보이지 않았다. 차후 실제 reference string 데이터를 이용해 시뮬레이션해보면 또 다른 흐름의 결과가 나올 수 있을 것 같다.