<script lang="ts">
  import { RadioGroup, RadioItem } from '@skeletonlabs/skeleton';
  import { Toast, getToastStore } from '@skeletonlabs/skeleton';
  import type { ToastSettings, ToastStore } from '@skeletonlabs/skeleton';
  import { initializeStores } from '@skeletonlabs/skeleton';
  import { CodeBlock } from '@skeletonlabs/skeleton';
  initializeStores();
  const toastStore = getToastStore();

  const toastSettingNormal: ToastSettings = {
    message: 'Lorem ipsum dolor sit amet consectetur adipisicing elit...',
  };

  const toastSettingError: ToastSettings = {
    message: 'This message will have a colorful background.',
    // Provide any utility or variant background style:
    background: 'variant-filled-error',
  };
  let value: number = 0;
</script>

<div class="root">
  <div>
    <a href="https://www.skeleton.dev/">Link : Skeleton Home</a>
  </div>
  <div>
    <a href="https://www.skeleton.dev/components/radio-groups"
      >Link : Skeleton RadioGroup</a
    >
  </div>
  <div style="height:20px"></div>
  <CodeBlock language="html" code="{`<div>This is meta</div>`}" />
  <div style="height:20px"></div>
  <div>
    <button on:click="{() => toastStore.trigger(toastSettingNormal)}"
      >Open Normal Toast</button
    >
  </div>
  <div>
    <button on:click="{() => toastStore.trigger(toastSettingError)}"
      >Open Error Toast</button
    >
  </div>
  <div>
    <RadioGroup>
      <RadioItem bind:group="{value}" name="justify" value="{0}">User</RadioItem
      >
      <RadioItem bind:group="{value}" name="justify" value="{1}"
        >Accont</RadioItem
      >
      <RadioItem bind:group="{value}" name="justify" value="{2}"
        >Target</RadioItem
      >
    </RadioGroup>
  </div>
  <Toast />
</div>

<style lang="scss">
  .root {
    padding: 12px;
  }
</style>
