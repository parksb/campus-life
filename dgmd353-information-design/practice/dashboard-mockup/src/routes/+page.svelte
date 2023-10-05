<script>
  import 'carbon-components-svelte/css/all.css';
  import { ImageLoader, Dropdown } from "carbon-components-svelte";
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
            <h3>Table</h3>
          </div>
          <div class="mcard row">
            <h3>Table</h3>
          </div>
        </div>
        <div class="col">
          <div class="mcard row">
            <h3>Table</h3>
          </div>
          <div class="mcard row">
            <h3>Table</h3>
          </div>
        </div>
        <div class="mcard col">
          <h3>국제학술지 논문</h3>
          <ImageLoader src="https://50history.ajou.ac.kr/img/sub02_05/graph03_04.jpg" />
        </div>
      </div>
      <h2>교육</h2>
      <div class="row">
        <div class="mcard col">
          <h3>누적 교환학생</h3>
          <ImageLoader src="https://50history.ajou.ac.kr/img/sub02_05/graph03_03.svg" />
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
