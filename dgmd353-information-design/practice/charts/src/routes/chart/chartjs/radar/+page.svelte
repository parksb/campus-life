<script lang="ts">
  import { Chart } from 'chart.js/auto';

  let eleRoot: HTMLCanvasElement;
  let chart: Chart;

  const data = {
    labels: [
      'Eating',
      'Drinking',
      'Sleeping',
      'Designing',
      'Coding',
      'Cycling',
      'Running'
    ],
    datasets: [{
      label: 'My First Dataset',
      data: [65, 59, 90, 81, 56, 55, 40],
      fill: true,
      backgroundColor: 'rgba(255, 99, 132, 0.2)',
      borderColor: 'rgb(255, 99, 132)',
      pointBackgroundColor: 'rgb(255, 99, 132)',
      pointBorderColor: '#fff',
      pointHoverBackgroundColor: '#fff',
      pointHoverBorderColor: 'rgb(255, 99, 132)'
    }, {
        label: 'My Second Dataset',
        data: [78, 78, 70, 79, 86, 87, 80],
        fill: true,
        backgroundColor: 'rgba(54, 162, 235, 0.2)',
        borderColor: 'rgb(54, 162, 235)',
        pointBackgroundColor: 'rgb(54, 162, 235)',
        pointBorderColor: '#fff',
        pointHoverBackgroundColor: '#fff',
        pointHoverBorderColor: 'rgb(54, 162, 235)'
      }]
  };

  $: {
    if (eleRoot) {
      chart = new Chart(eleRoot, {
        type: 'radar',
        data: data,
        options: {
          elements: {
            line: {
              borderWidth: 1,
            },
          },
        },
      });
    }
  }
</script>

<div class="root">
  <canvas class="root" bind:this="{eleRoot}"></canvas>
</div>

<style lang="scss">
  .root {
    height: 400px;
  }
</style>
