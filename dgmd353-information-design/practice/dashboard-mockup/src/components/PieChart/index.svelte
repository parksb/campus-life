<script lang="ts">
  import * as d3 from 'd3';

  export let data: { y: number, k: string, c: string }[] = [];

  let el: HTMLElement;

  const width = 240;
  const height = Math.min(width, 500);

  const radius = Math.min(width, height) / 2;

  const arc = d3.arc()
      .innerRadius(radius)
      .outerRadius(0);

  const pie = d3.pie()
      .padAngle(1 / radius)
      .sort(null)
      .value(d => d.y);

  const color = d3.scaleOrdinal()
      .domain(data.map(d => d.k))
      .range(d3.quantize(t => d3.interpolateSpectral(t * 0.8 + 0.1), data.length).reverse());

  const svg = d3.create("svg")
      .attr("width", width)
      .attr("height", height)
      .attr("viewBox", [-width / 2, -height / 2, width, height])
      .attr("style", "max-width: 100%; height: auto;");

  svg.append("g")
    .selectAll()
    .data(pie(data))
    .join("path")
      .attr("fill", d => (d.data.c))
      .attr("d", arc)
    .append("title")
      .text(d => `${d.data.k}: ${d.data.y}명`);

  svg.append("g")
      .attr("font-family", "sans-serif")
      .attr("font-size", 12)
      .attr("text-anchor", "middle")
    .selectAll()
    .data(pie(data))
    .join("text")
      .attr("transform", d => `translate(${arc.centroid(d)})`)
      .call(text => text.append("tspan")
          .attr("y", "-0.4em")
          .attr("font-weight", "bold")
          .text(d => d.data.k))
      .call(text => text.filter(d => (d.endAngle - d.startAngle) > 0.25).append("tspan")
          .attr("x", 0)
          .attr("y", "0.7em")
          .attr("fill-opacity", 0.7)
          .text(d => d.data.y));

  $: {
    el?.firstChild?.remove();
    el?.append(svg.node()!!);
  }
</script>

<div bind:this={el} role="img" />
