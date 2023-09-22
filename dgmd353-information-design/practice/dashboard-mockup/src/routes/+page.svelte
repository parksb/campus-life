<script>
  import 'carbon-components-svelte/css/all.css';
  import { Dropdown, ImageLoader } from "carbon-components-svelte";
</script>

<div class="root">
  <div class="side">
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
      <div class="row">
        <div class="col">
          <div class="mcard row"></div>
          <div class="mcard row"></div>
        </div>
        <div class="col">
          <div class="mcard row"></div>
          <div class="mcard row"></div>
        </div>
        <div class="mcard col"></div>
      </div>
      <div class="row">
        <div class="mcard col"></div>
        <div class="mcard col"></div>
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
    width: 230px;
    height: 100%;
    padding: 1rem;
    background-color: #333a45;
  }

  .main {
    width: 100%;
    height: 100%;
    background-color: #f3f4f7;

    .body {
      display: flex;
      flex-direction: column;
      padding: 1rem;

      .col {
        flex-direction: column;
      }

      .mcard {
        background-color: #ffffff;
        margin: 5px;
        padding: 1rem;
        box-shadow: 0 0 5px #f0f0f0;
      }

      .col, .row {
        display: flex;
        flex: 1;
      }
    }
  }

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

</style>
