import { presetAtoUI } from 'ato-ui/preset';
import { defineConfig } from 'unocss';

import presetIcons from '@unocss/preset-icons';
import presetWind from '@unocss/preset-wind';
import transformerDirectives from '@unocss/transformer-directives';
import transformerVariantGroup from '@unocss/transformer-variant-group';

export default defineConfig({
  presets: [
    presetIcons({
      extraProperties: {
        display: 'inline-block',
        'vertical-align': 'middle',
      },
    }),
    presetWind(),
    presetAtoUI(),
  ],
  transformers: [transformerVariantGroup(), transformerDirectives()],
});
