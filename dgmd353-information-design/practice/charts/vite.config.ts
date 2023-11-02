//@ts-ignore
import path from 'path';
import { defineConfig } from 'vite';

import { sveltekit } from '@sveltejs/kit/vite';

//@ts-ignore

export default defineConfig({
  plugins: [sveltekit()],

  resolve: {
    alias: {
      //@ts-ignore
      '@': path.resolve(__dirname, 'src'),
    },
  },
});
