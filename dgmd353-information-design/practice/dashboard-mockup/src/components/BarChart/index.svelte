<script lang="ts">
  import * as Plot from "@observablehq/plot";

  export let data: { x: number, y: number }[] = [];

  let el: HTMLElement;

  $: {
    el?.firstChild?.remove();
    el?.append(
      Plot.plot({
        marginLeft: 30,
        marginRight: 5,
        height: 800,
        label: null,
        y: { grid: true, nice: true },
        marks: [
          Plot.barY(data, { x: 'x', y: 'y', fill: '#1482bb' }),
          Plot.text(data, Plot.pointerX({ x: 'x', y: 'y', dy: -10, text: (d) => `${d.y}편` })),
          Plot.axisX({ tickFormat: '', interval: 5 }),
          Plot.axisY({ interval: 100 }),
          Plot.ruleY([0]),
        ],
      })
    );
  }
</script>

<div bind:this={el} role="img" />
