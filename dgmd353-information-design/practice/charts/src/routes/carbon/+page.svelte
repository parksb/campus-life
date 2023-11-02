<script lang="ts">
  import 'carbon-components-svelte/css/all.css';

  import { Grid, Row, Column, Tag } from 'carbon-components-svelte';

  import { Button } from 'carbon-components-svelte';
  import { Search } from 'carbon-components-svelte';
</script>

<div class="root">
  <h4>Button</h4>
  <a href="https://carbon-components-svelte.onrender.com/components/Button"
    >https://carbon-components-svelte.onrender.com/components/Button</a
  >
  <div style="height:10px"></div>
  <Grid>
    <Row>
      <Column>
        <Button>Primary button</Button>
      </Column>
      <Column>
        <Button kind="secondary">Secondary button</Button>
      </Column>
      <Column>
        <Button kind="tertiary">Tecondary button</Button>
      </Column>
      <Column>
        <Button kind="danger">Decondary button</Button>
      </Column>
    </Row>
  </Grid>
  <div style="height:30px"></div>
  <h4>Tag</h4>
  <a href="https://carbon-components-svelte.onrender.com/components/Tag"
    >https://carbon-components-svelte.onrender.com/components/Tag</a
  >
  <div></div>
  <div style="height:10px"></div>
  <Tag type="red">red</Tag>
  <Tag type="magenta">magenta</Tag>
  <Tag type="purple">purple</Tag>
  <Tag type="blue">blue</Tag>
  <Tag type="cyan">cyan</Tag>
  <Tag type="teal">teal</Tag>
  <Tag type="green">green</Tag>
  <Tag type="gray">gray</Tag>
  <Tag type="cool-gray">cool-gray</Tag>
  <Tag type="warm-gray">warm-gray</Tag>
  <Tag type="high-contrast">high-contrast</Tag>
  <Tag type="outline">outline</Tag>
  <div style="height:30px"></div>
  <h4>Button</h4>
  <a href="https://carbon-components-svelte.onrender.com/components/Search"
    >https://carbon-components-svelte.onrender.com/components/Search</a
  >
  <div style="height:10px"></div>
  <Search />
</div>

<style lang="scss">
  .root {
    padding: 20px;
  }
</style>
