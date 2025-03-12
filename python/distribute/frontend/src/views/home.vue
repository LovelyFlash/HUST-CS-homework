<template>
	<v-header />
	<v-sidebar />
	<div class="content-box" :class="{ 'content-collapse': sidebar.collapse }">
		<v-tags></v-tags>
		<div class="content" ref="ctn_box">
			<router-view v-slot="{ Component }" :passData="ctn_box">
				<keep-alive :max="6">
					<component :is="Component"></component>
				</keep-alive>
			</router-view>
		</div>
	</div>
	<!-- <el-backtop :right="100" :bottom="100" /> -->
</template>
<script setup lang="ts">
import { defineAsyncComponent, provide, ref, onMounted } from 'vue';
// import { ElBacktop } from 'element-plus';
import { useSidebarStore } from '../store/sidebar';
import { useTagsStore } from '../store/tags';
import vHeader from '../components/header.vue';
import vSidebar from '../components/sidebar.vue';
import vTags from '../components/tags.vue';
const ctn_box = ref<HTMLElement>();

const sidebar = useSidebarStore();
const tags = useTagsStore();
// console.log(tags.nameList);
const emit = defineAsyncComponent(() => import('./studentInformation.vue'))
const name = ref('home')
provide('name', name)

onMounted(() => {
  console.log(ctn_box);
});

const scrollToT = () => {
	ctn_box.value?.scrollTo(0,0);
}

</script>
