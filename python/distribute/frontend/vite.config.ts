import { defineConfig } from 'vite';
import vue from '@vitejs/plugin-vue';
import VueSetupExtend from 'vite-plugin-vue-setup-extend';
import AutoImport from 'unplugin-auto-import/vite';
import Components from 'unplugin-vue-components/vite';
import { ElementPlusResolver } from 'unplugin-vue-components/resolvers';
export default defineConfig({
	base: './',
	plugins: [
		vue(),
		VueSetupExtend(),
		AutoImport({
			resolvers: [ElementPlusResolver()]
		}),
		Components({
			resolvers: [ElementPlusResolver()]
		})
	],
	optimizeDeps: {
		include: ['schart.js']
	},
	// 解决跨域问题
	server: {
		hmr: true,
		host: '0.0.0.0',
		port: 3000,
		proxy: {
		  '/proxy': {
			target: 'http://127.0.0.1:8888',	//实际请求地址
			changeOrigin: true,
			rewrite: (path) => path.replace(/^\/proxy/, '')
		  },
		}
	  }
});
