<script lang="ts">
  import { Alert, Spinner, Button, Badge, Avatar, Card } from 'flowbite-svelte';
  import { ArrowRightOutline } from 'flowbite-svelte-icons';
</script>

<div class="p-8">
  <Alert>
    <span class="font-medium">Info alert!</span>
    Change a few things up and try submitting again.
  </Alert>
</div>
<div class="p-8">
  <Spinner />
  <Spinner color="gray" />
  <Spinner color="green" />
  <Spinner color="red" />
  <Spinner color="yellow" />
  <Spinner color="pink" />
  <Spinner color="purple" />
</div>
<div class="p-8">
  <Button>Default</Button>
  <Button color="alternative">Alternative</Button>
  <Button color="dark">Dark</Button>
  <Button color="light">Light</Button>
  <Button color="blue">Blue</Button>
  <Button color="green">Green</Button>
  <Button color="red">Red</Button>
  <Button color="yellow">Yellow</Button>
  <Button color="purple">Purple</Button>
</div>
<div class="p-8">
  <Badge>Default</Badge>
  <Badge color="dark">Dark</Badge>
  <Badge color="red">Red</Badge>
  <Badge color="green">Green</Badge>
  <Badge color="yellow">Yellow</Badge>
  <Badge color="indigo">Indigo</Badge>
  <Badge color="purple">Purple</Badge>
  <Badge color="pink">Pink</Badge>
</div>

<div class="p-8">
  <Avatar />
  <Avatar rounded />
  <Avatar border />
  <Avatar rounded border />
</div>

<div class="p-8">
  <Card>
    <h5
      class="mb-2 text-2xl font-bold tracking-tight text-gray-900 dark:text-white"
    >
      Noteworthy technology acquisitions 2021
    </h5>
    <p class="mb-3 font-normal text-gray-700 dark:text-gray-400 leading-tight">
      Here are the biggest enterprise technology acquisitions of 2021 so far, in
      reverse chronological order.
    </p>
    <Button class="w-fit">
      Read more <ArrowRightOutline class="w-3.5 h-3.5 ml-2 text-white" />
    </Button>
  </Card>
</div>
