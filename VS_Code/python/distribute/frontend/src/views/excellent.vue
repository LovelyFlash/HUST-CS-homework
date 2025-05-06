<template>
	<div class="container">
		<div class="plugins-tips">
			优良学风班情况
		</div>
		<div class="schart-box">
			<div class="content-title">优良学风班数量及比例</div>
			<ExcellentBar />
		</div>
		<div class="schart-box">
			<div class="content-title">各年级优良学风班比例</div>
			<ExcellentLine1 />
		</div>
	</div>
</template>

<script setup lang="ts" name="basecharts">
import { onMounted } from "vue-demi";
import ExcellentBar from "../components/excellentBar.vue";
import ExcellentLine1 from "../components/excellentLine1.vue";
import { useTagsStore } from '../store/tags';

const tags = useTagsStore();
console.log(tags.nameList);
onMounted(() => {
	console.log("excellent");
})
</script>

<style scoped>
.container{
	box-sizing: border-box;
	width: 100%;
	height: 100%;
}
.schart-box {
	display: inline-block;
	width: 50%;
	height: 100%;
}

.schart {
	width: 600px;
	height: 400px;
}

.content-title {
	clear: both;
	font-weight: 400;
	line-height: 50px;
	margin: 10px 0;
	margin-left: 10px;
	font-size: 22px;
	color: #1f2f3d;
	text-align: center;
}
</style>
