<script lang="ts">
  import 'carbon-components-svelte/css/all.css';
  import { ImageLoader, Dropdown } from "carbon-components-svelte";
  import * as Plot from "@observablehq/plot";

  let xchgChart: HTMLElement;
  let xchgdata = [
    { x: 1999, y: 0, k: '#4589ba' }, { x: 2003, y: 155, k: '#4589ba' }, { x: 2010, y: 1255, k: '#4589ba' }, { x: 2013, y: 3349, k: '#4589ba' }, { x: 2022, y: 5963, k: '#4589ba' },
    { x: 1999, y: 0, k: '#92b9de' }, { x: 2003, y: 355, k: '#92b9de' }, { x: 2010, y: 3055, k: '#92b9de' }, { x: 2013, y: 4349, k: '#92b9de' }, { x: 2022, y: 8963, k: '#92b9de' },
  ];
  $: {
    xchgChart?.firstChild?.remove();
    xchgChart?.append(
      Plot.plot({
        label: null,
        y: { grid: true },
        marks: [
          Plot.areaY(xchgdata, { x: 'x', y: 'y', fill: 'k' }),
          Plot.axisX({ tickFormat: '', interval: 5 }),
        ],
      })
    );
  }

  let sciChart: HTMLElement;
  let sciData = [{ x: 2003, y: 112 }, { x: 2004, y: 110 }, { x: 2005, y: 120 }, { x: 2006, y: 180 },
    { x: 2007, y: 190 }, { x: 2008, y: 200 }, { x: 2009, y: 230 }, { x: 2010, y: 240 },
    { x: 2011, y: 270 }, { x: 2012, y: 380 }, { x: 2013, y: 377 }, { x: 2014, y: 340 },
    { x: 2015, y: 370 }, { x: 2016, y: 390 }, { x: 2017, y: 380 }, { x: 2018, y: 400 },
    { x: 2019, y: 370 }, { x: 2020, y: 410 }, { x: 2021, y: 430 }, { x: 2022, y: 513 }];

  $: {
    sciChart?.firstChild?.remove();
    sciChart?.append(
      Plot.plot({
        label: null,
        y: { grid: true },
        marks: [
          Plot.barY(sciData, { x: 'x', y: 'y', fill: '#4589ba' }),
          Plot.lineY(sciData, { x: 'x', y: 'y', stroke: '#92b9de' }),
          Plot.text(sciData, Plot.pointer({ x: 'x', y: 'y', dy: -10, text: (d) => d.y })),
          Plot.axisX({ tickFormat: '', interval: 5 }),
          Plot.axisY({ interval: 100 }),
        ],
      })
    );
  }
</script>

<div class="root">
  <div class="side">
    <ImageLoader src="https://50.ajou.ac.kr/assets/img/50th_em_color02.png" />
  </div>
  <div class="main">
    <div class="header">
      <Dropdown
        class="dropdown"
        selectedId="0"
        items={[
          { id: "0", text: "Korean" },
          { id: "1", text: "English" },
        ]}
      />
    </div>
    <div class="body">
      <h2>연구</h2>
      <div class="row">
        <div class="col">
          <div class="mcard row">
            <h3>전임교원</h3>
          </div>
          <div class="mcard row">
            <h3>직원</h3>
          </div>
        </div>
        <div class="col">
          <div class="mcard row">
            <h3>연속간행물</h3>
          </div>
          <div class="mcard row">
            <h3>비도서자료</h3>
          </div>
        </div>
        <div class="mcard col">
          <h3>국제학술지 논문</h3>
          <div bind:this={sciChart} role="img" />
        </div>
      </div>
      <h2>교육</h2>
      <div class="row">
        <div class="mcard col">
          <h3>누적 교환학생</h3>
          <div bind:this={xchgChart} role="img" />
        </div>
        <div class="mcard col">
          <h3>누적 유학생</h3>
          <ImageLoader src="https://50history.ajou.ac.kr/img/sub02_05/graph03_02.svg" />
        </div>
      </div>
    </div>
  </div>
</div>

<style lang="scss">
  .root {
    display: flex;
    width: 100%;
    height: 100vh;
  }

  .side {
    width: 200px;
    height: 100%;
    padding: 1rem;
    background-color: #333a45;
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

      .dropdown {
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
        background-color: #ffffff;
        margin: 5px;
        padding: 1rem;
        box-shadow: 0 0 5px #f0f0f0;
        flex-direction: column;
        justify-content: space-between;

        & > h3 {
          font-size: 1.2rem;
        }
      }

      .col, .row {
        display: flex;
        flex: 1;
      }
    }
  }
</style>
