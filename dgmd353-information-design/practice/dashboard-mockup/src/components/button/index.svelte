<script lang="ts">
  export let name: string = '';
</script>

<div class="button" on:click>
  {name}
</div>

<style lang="scss">
  .button {
    width: 100px;
    height: 30px;
    background-color: red;
  }
</style>
