<script lang="ts">
  import c3 from 'c3';

  let ele: HTMLDivElement;
  $: {
    console.log({ c3 });
    let chart = c3.generate({
      bindto: ele,
      data: {
        columns: [
          ['data1', 30, 200, 100, 400, 150, 250],
          ['data2', 50, 20, 10, 40, 15, 25],
        ],
      },
    });
  }
</script>

<div class="root">
  <div id="chart" bind:this="{ele}"></div>
</div>

<style lang="scss">
  .root {
    height: 400px;
    #chart {
      height: 100%;
    }
  }
</style>
