//@ts-ignore
import path from 'path';
import UnoCSS from 'unocss/vite';
import { defineConfig } from 'vite';

import { sveltekit } from '@sveltejs/kit/vite';

//@ts-ignore

export default defineConfig({
  plugins: [sveltekit(), UnoCSS()],

  resolve: {
    alias: {
      //@ts-ignore
      '@': path.resolve(__dirname, 'src'),
    },
  },
});
