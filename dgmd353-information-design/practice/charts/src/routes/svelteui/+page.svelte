<script lang="ts">
  import {
    AppShell,
    Badge,
    Button,
    Card,
    Center,
    Grid,
    Group,
    Header,
    Image,
    Space,
    Tabs,
    Text,
    Title,
  } from '@svelteuidev/core';
  import { Camera, EnvelopeClosed, Gear } from 'radix-icons-svelte';
  let isDark = false;
  let opened = true;

  function toggleTheme() {
    isDark = !isDark;
  }
  function toggleOpened() {
    opened = !opened;
  }
</script>

<AppShell>
  <Header slot="header" height="48px">
    <Center>
      <Title order="{4}">Project Sample</Title>
    </Center>
  </Header>

  <slot>
    <Title order="{4}">Grid</Title>
    <Space h="{12}" />
    <Group grow noWrap>
      <Button variant="outline">1</Button>
      <Button variant="outline">2</Button>
      <Button variant="outline">3</Button>
    </Group>
    <Space h="{42}" />
    <Title order="{4}">Tabs</Title>
    <Space h="{12}" />
    <Tabs>
      <Tabs.Tab label="Gallery" icon="{Camera}">Gallery tab content</Tabs.Tab>
      <Tabs.Tab label="Messages" icon="{EnvelopeClosed}"
        >Messages tab content</Tabs.Tab
      >
      <Tabs.Tab label="Settings" icon="{Gear}">Settings tab content</Tabs.Tab>
    </Tabs>
    <Space h="{42}" />
    <Title order="{4}">Card</Title>
    <Space h="{12}" />

    <Grid>
      <Grid.Col span="{4}">
        <Card shadow="sm" padding="lg">
          <Card.Section first padding="lg">
            <Image
              src="https://files.muzli.cloud/ad5a5214340bea6140a64fbc08d239fc.jpeg"
              height="{160}"
              alt="Portugal"
            />
          </Card.Section>

          <Group position="apart">
            <Text weight="{500}">Portugal Porto Adventures</Text>
            <Badge color="pink" variant="light">On Sale</Badge>
          </Group>

          <Text size="sm">
            With Portugal Porto Adventures you can explore more of the beautiful
            portuguese cities, by walking on food, meeting the locals and eat
            excellent food and wine
          </Text>

          <Button variant="light" color="blue" fullSize>
            Book classic tour now
          </Button>
        </Card>
      </Grid.Col>
      <Grid.Col span="{4}">2</Grid.Col>
      <Grid.Col span="{4}">3</Grid.Col>
    </Grid>
  </slot>
</AppShell>
