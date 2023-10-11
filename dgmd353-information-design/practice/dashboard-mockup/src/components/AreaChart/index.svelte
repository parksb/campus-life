<script lang="ts">
  import * as Plot from "@observablehq/plot";

  export let data: { x: number, y: number, k: string }[] = [];

  let el: HTMLElement;

  $: {
    el?.firstChild?.remove();
    el?.append(
      Plot.plot({
        marginTop: 0,
        marginRight: 0,
        marginBottom: 20,
        marginLeft: 45,
        width: 960,
        color: { scheme: 'Blues', legend: true },
        label: null,
        y: { grid: true },
        marks: [
          Plot.areaY(data, { x: 'x', y: 'y', fill: 'k', stroke: 'k' }),
          Plot.axisX({ tickFormat: '', interval: 5 }),
          Plot.ruleY([0]),
        ],
      })
    );
  }
</script>

<div bind:this={el} role="img" />
