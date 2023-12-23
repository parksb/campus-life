<script lang="ts">
  import { type ChainInfo } from '@src/lib';
  import { type IChartApi, createChart } from 'lightweight-charts';
  import { requestGet } from '@src/lib/requester';
  import moment from 'moment';
  import _ from 'lodash';
  import {
    Table,
    TableBody,
    TableBodyCell,
    TableBodyRow,
    TableHead,
    TableHeadCell,
  } from 'flowbite-svelte';

  let data: ChainInfo;
  const promiseData = requestGet<ChainInfo>('/data/archway.json').then((d) => {
    data = d;
    return d;
  });
  let eleLineGraph: HTMLDivElement;
  let eleLineGraphWidth: number;
  let eleLineGraphHeight: number;
  let chart: IChartApi;
  $: {
    if (eleLineGraph && data) {
      chart && chart.remove();
      chart = createChart(eleLineGraph, {
        width: eleLineGraphWidth,
        height: eleLineGraphHeight,
      });
      const lineSeries = chart.addLineSeries();
      const series = _(data.data)
        .map((unit) => {
          const time = moment(unit.createdAt._seconds * 1000).format(
            'YYYY-MM-DD'
          );
          const value = unit.unit.market.values[0];
          return {
            time,
            value: value || 0,
          };
        })
        .uniqBy('time')
        .orderBy('time', 'asc')
        .value();

      lineSeries.setData(series);
    }
  }
</script>

<div class="root">
  <div class="container">
    <div class="title">Price Graph</div>
    <div
      class="area"
      bind:this="{eleLineGraph}"
      bind:clientWidth="{eleLineGraphWidth}"
      bind:clientHeight="{eleLineGraphHeight}"
    ></div>
  </div>
  <div class="table-container">
    {#await promiseData}
      <div>Loading...</div>
    {:then data}
      <Table>
        <TableHead>
          <TableHeadCell>Date</TableHeadCell>
          <TableHeadCell>APY</TableHeadCell>
          <TableHeadCell>Category</TableHeadCell>
          <TableHeadCell>Price</TableHeadCell>
        </TableHead>
        <TableBody>
          {#each data.data as datum}
            <TableBodyRow>
              <TableBodyCell
                >{moment(datum.createdAt._seconds * 1000).format(
                  'YYYY-MM-DD HH:mm:ss'
                )}</TableBodyCell
              >
              <TableBodyCell>{Math.floor(datum.unit.apr * 100)}%</TableBodyCell>
              <TableBodyCell>{datum.unit.market.values[5]}</TableBodyCell>
              <TableBodyCell>{datum.unit.market.values[8]}</TableBodyCell>
            </TableBodyRow>
          {/each}
        </TableBody>
      </Table>
    {:catch error}
      <div>{error.message}</div>
    {/await}
  </div>
</div>

<style lang="scss">
  .root {
    height: 100vh;
    display: grid;
    grid-template-rows: 400px 1fr;
    padding: 12px;
    .container {
      height: 100%;
      display: grid;
      grid-template-rows: 32px 1fr;

      border: solid 1px #ccc;
      .title {
        line-height: 32px;
        font-size: 14px;
        font-weight: 600;
        padding: 0 12px;
        border-bottom: solid 1px #ccc;
      }
      .container {
        width: 100%;
        height: 100%;
      }
    }
    .table-container {
      height: 100%;
      overflow-y: scroll;
    }
  }
</style>
