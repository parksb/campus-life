<script lang="ts">
  import 'carbon-components-svelte/css/all.css';
  import {
    ImageLoader,
    Dropdown,
    StructuredList,
    StructuredListHead,
    StructuredListRow,
    StructuredListCell,
    StructuredListBody,
  } from "carbon-components-svelte";

  import BarChart from "../components/BarChart/index.svelte";
  import AreaChart from "../components/AreaChart/index.svelte";
  import PieChart from "../components/PieChart/index.svelte";

  let eduData = [{ y: 9705, k: '학부', c: '#1482bb' }, { y: 4007, k: '일반대학원', c: '#64a2db' }, { y: 3107, k: '특수대학원', c: '#98cadf' }, { y: 1913, k: '전문대학원', c: '#ddebf7' }];

  let sciData = [{ x: 2003, y: 112 }, { x: 2004, y: 110 }, { x: 2005, y: 120 }, { x: 2006, y: 180 },
    { x: 2007, y: 190 }, { x: 2008, y: 200 }, { x: 2009, y: 230 }, { x: 2010, y: 240 },
    { x: 2011, y: 270 }, { x: 2012, y: 380 }, { x: 2013, y: 377 }, { x: 2014, y: 340 },
    { x: 2015, y: 370 }, { x: 2016, y: 390 }, { x: 2017, y: 380 }, { x: 2018, y: 400 },
    { x: 2019, y: 370 }, { x: 2020, y: 410 }, { x: 2021, y: 430 }, { x: 2022, y: 513 }];

  let xchgData = [
    { x: 1999, y: 0, k: '교환학생' }, { x: 2003, y: 155, k: '교환학생' }, { x: 2010, y: 1255, k: '교환학생' },
    { x: 2013, y: 3349, k: '교환학생' }, { x: 2022, y: 5963, k: '교환학생' },
    { x: 1999, y: 0, k: '유치학생' }, { x: 2003, y: 355, k: '유치학생' }, { x: 2010, y: 3055, k: '유치학생' },
    { x: 2013, y: 4349, k: '유치학생' }, { x: 2022, y: 8963, k: '유치학생' },
  ];

  let frgData = [
    { x: 1996, y: 0, k: '학부' }, { x: 2003, y: 260, k: '학부' }, { x: 2010, y: 2833, k: '학부' }, { x: 2013, y: 5349, k: '학부' }, { x: 2022, y: 8005, k: '학부' },
    { x: 1996, y: 0, k: '대학원' }, { x: 2003, y: 155, k: '대학원' }, { x: 2010, y: 1255, k: '대학원' }, { x: 2013, y: 3349, k: '대학원' }, { x: 2022, y: 5963, k: '대학원' },
    { x: 1996, y: 0, k: '국제대학원' }, { x: 2003, y: 355, k: '국제대학원' }, { x: 2010, y: 3055, k: '국제대학원' }, { x: 2013, y: 4349, k: '국제대학원' }, { x: 2022, y: 2963, k: '국제대학원' },
  ];
</script>

<div class="root">
  <div class="side">
    <div class="logo">
      <ImageLoader src="https://50.ajou.ac.kr/assets/img/50th_em_color02.png" />
    </div>
    <ul>
      <li class="selected">Overview</li>
      <li>Menu</li>
      <li>Menu</li>
      <li>Menu</li>
    </ul>
  </div>
  <div class="main">
    <div class="header">
      <div class="dropdown">
        <Dropdown
          class="dropdown"
          selectedId="0"
          items={[
            { id: "0", text: "한국어" },
            { id: "1", text: "English" },
          ]}
        />
      </div>
    </div>
    <div class="body">
      <h2>연구</h2>
      <div class="row">
        <div class="col">
          <div class="mcard row">
            <h3>재학생</h3>
            <PieChart data={eduData} />
          </div>
          <div class="mcard row">
            <h3>A</h3>
            <StructuredList>
              <StructuredListHead>
                <StructuredListRow head>
                  <StructuredListCell head>A</StructuredListCell>
                  <StructuredListCell head>B</StructuredListCell>
                  <StructuredListCell head>C</StructuredListCell>
                </StructuredListRow>
              </StructuredListHead>
              <StructuredListBody>
                <StructuredListRow>
                  <StructuredListCell noWrap>A</StructuredListCell>
                  <StructuredListCell>Row 1</StructuredListCell>
                  <StructuredListCell>Lorem ipsum dolor sit amet, consectetur.</StructuredListCell>
                </StructuredListRow>
                <StructuredListRow>
                  <StructuredListCell noWrap>Row 2</StructuredListCell>
                  <StructuredListCell>Row 2</StructuredListCell>
                  <StructuredListCell>Lorem ipsum dolor sit amet, consectetur.</StructuredListCell>
                </StructuredListRow>
              </StructuredListBody>
            </StructuredList>
          </div>
        </div>
        <div class="col">
          <div class="mcard row">
            <h3>B</h3>
            <StructuredList>
              <StructuredListHead>
                <StructuredListRow head>
                  <StructuredListCell head>A</StructuredListCell>
                  <StructuredListCell head>B</StructuredListCell>
                  <StructuredListCell head>C</StructuredListCell>
                </StructuredListRow>
              </StructuredListHead>
              <StructuredListBody>
                <StructuredListRow>
                  <StructuredListCell noWrap>Row 1</StructuredListCell>
                  <StructuredListCell>Row 1</StructuredListCell>
                  <StructuredListCell>Lorem ipsum dolor sit amet, consectetur.</StructuredListCell>
                </StructuredListRow>
                <StructuredListRow>
                  <StructuredListCell noWrap>Row 2</StructuredListCell>
                  <StructuredListCell>Row 2</StructuredListCell>
                  <StructuredListCell>Lorem ipsum dolor sit amet, consectetur.</StructuredListCell>
                </StructuredListRow>
              </StructuredListBody>
            </StructuredList>
          </div>
          <div class="mcard row">
            <h3>C</h3>
            <StructuredList>
              <StructuredListHead>
                <StructuredListRow head>
                  <StructuredListCell head>A</StructuredListCell>
                  <StructuredListCell head>B</StructuredListCell>
                  <StructuredListCell head>C</StructuredListCell>
                </StructuredListRow>
              </StructuredListHead>
              <StructuredListBody>
                <StructuredListRow>
                  <StructuredListCell noWrap>Row 1</StructuredListCell>
                  <StructuredListCell>Row 1</StructuredListCell>
                  <StructuredListCell>Lorem ipsum dolor sit amet, consectetur.</StructuredListCell>
                </StructuredListRow>
                <StructuredListRow>
                  <StructuredListCell noWrap>Row 2</StructuredListCell>
                  <StructuredListCell>Row 2</StructuredListCell>
                  <StructuredListCell>Lorem ipsum dolor sit amet, consectetur.</StructuredListCell>
                </StructuredListRow>
              </StructuredListBody>
            </StructuredList>
          </div>
        </div>
        <div class="mcard col">
          <h3>국제학술지 논문</h3>
          <BarChart data={sciData} />
        </div>
      </div>
      <h2>교육</h2>
      <div class="row">
        <div class="mcard col">
          <h3>누적 교환학생</h3>
          <AreaChart data={xchgData} />
        </div>
        <div class="mcard col">
          <h3>누적 유학생</h3>
          <AreaChart data={frgData} />
        </div>
      </div>
    </div>
  </div>
</div>

<style lang="scss">
  .bx--structured-list {
    margin: 0 !important;
  }

  .root {
    display: flex;
    width: 100%;
    height: 100vh;
  }

  .side {
    width: 200px;
    height: 100%;
    background-color: #333a45;

    .logo {
      padding: .5rem;
      margin-bottom: 1rem;
    }

    & > ul {
      width: 100%;
      list-style: none;

      & > li {
        color: #ffffff;
        padding: 1rem 1.5rem;
        width: 100%;
        cursor: pointer;

        &:hover {
          background-color: #25699a;
        }

        &.selected {
          background-color: #25699a;
        }
      }
    }
  }

  .main {
    width: 100%;
    height: 100%;
    background-color: #f3f4f7;

    .header {
      display: flex;
      width: 100%;
      height: 60px;
      padding: 1rem;
      background-color: #ffffff;
      justify-content: flex-end;
      align-items: center;

      & > .dropdown {
        width: 150px;
      }
    }

    .body {
      display: flex;
      flex-direction: column;
      padding: 1.5rem;
      overflow: auto;
      height: calc(100% - 60px);

      .col {
        flex-direction: column;
      }

      .row {
        margin-bottom: 1rem;
      }

      .mcard {
        flex: 1;
        background-color: #ffffff;
        margin: 5px;
        padding: 1rem;
        box-shadow: 0 0 5px #f0f0f0;
        flex-direction: column;
        justify-content: space-between;

        & > h3 {
          font-size: 1.2rem;
          margin-bottom: 1rem;
        }
      }

      .col, .row {
        display: flex;
        flex: 1;
      }
    }
  }
</style>
