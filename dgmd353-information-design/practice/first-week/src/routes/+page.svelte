<script>
  import { Button } from 'flowbite-svelte';
  import { Card } from 'flowbite-svelte';
</script>

<h1>Hello, Svelte!</h1>

<div class="container">
  <div class="item">
    <Button>Default</Button>
    <Button color="alternative">Alternative</Button>
  </div>
  <div class="item">
    <Button color="dark">Dark</Button>
    <Button color="light">Light</Button>
  </div>
  <div class="item">
    <Button color="blue">Blue</Button>
    <Button color="green">Green</Button>
  </div>
  <div class="item">
    <Button color="red">Red</Button>
  </div>
  <div class="item">
    <Button color="yellow">Yellow</Button>
    <Button color="purple">Purple</Button>
  </div>
  <div class="item">
    <Card href="/cards">
      <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">Noteworthy technology acquisitions 2021</h5>
      <p class="font-normal text-gray-700 dark:text-gray-400 leading-tight">Here are the biggest enterprise technology acquisitions of 2021 so far, in reverse chronological order.</p>
    </Card>
  </div>
</div>



<style>
  div {
    display: grid;
  }

  .container {
    grid-template-columns: repeat(2, 1fr);
    grid-template-rows: repeat(3, 1fr);
  }

  .item {
    border: 1px black solid;
  }
</style>

