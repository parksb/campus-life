<script lang="ts">
  import { Chart } from 'chart.js/auto';
  import c3 from 'c3';
  import axios from 'axios';

  // chart.js

  let elchartjs: HTMLCanvasElement;

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
    if (elchartjs) {
      new Chart(elchartjs, {
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

  // c3.js

  let elpie: HTMLDivElement;

  let rawdata: any;

  let active: number = 0;
  let jailed: number = 0;

  (async () => {
    rawdata = (await axios.get('/cosmos.json')).data;
    active = rawdata.validators.active
    jailed = rawdata.validators.jailed
  })();

  $: {
    c3.generate({
      bindto: elpie,
      data: {
        type: 'pie',
        columns: [
          ['active', active],
          ['jailed', jailed],
        ],
      },
    });
  }
</script>

<div class="root">
  <canvas bind:this="{elchartjs}"></canvas>
  <div bind:this="{elpie}"></div>
</div>

<style lang="scss">
  .root {
    height: 400px;
  }
</style>
