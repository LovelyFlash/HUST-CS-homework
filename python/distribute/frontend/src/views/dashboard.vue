<template>
	<div>
		<el-row :gutter="20">
			<el-col :span="24">
				<template v-for="sub in dataset">
					<el-row :gutter="20">
						<template v-for="data in sub">
							<el-col :span="12">
								<el-card shadow="hover" :style="{height:data.major.length * 36 + 110 +'px'}">
									<template #header>
										<div class="clearfix">
											<span>{{ data.grade }}级学生 - 共{{ data.total }}人</span>
										</div>
									</template>
									<template v-for="item in data.major">
										<el-row>
											<el-col :span="6">
												{{ item.key }} - {{ item.value }}人
											</el-col>
											<el-col :span="18">
												<el-progress :percentage="item.rate" :text-inside="true" :stroke-width="20"></el-progress>
											</el-col>
										</el-row>
									</template>
								</el-card>
							</el-col>
						</template>
					</el-row>
				</template>
			</el-col>
		</el-row>
	</div>
</template>

<script setup lang="ts" name="dashboard">
// import Schart from 'vue-schart';
import { reactive, ref } from 'vue';
import { fetchEachGradeNumber } from '../api';
import { List, number } from 'echarts';
import { DataBoard } from '@element-plus/icons-vue';

interface majorItem {
	key: string;
	value: number;
	rate: number;
}

interface listItem {
	grade: string;
	total: number;
	major: majorItem[];
}

const name = localStorage.getItem('ms_username');
const role: string = localStorage.getItem('is_superuser') == 'true' ? '超级管理员' : '普通用户';
const majorMap = new Map<string, string>([["ALL", "全部"], ["CS", "计算机"], ["ACM", "ACM"], ["BSB", "本硕博(启明)"], ["IOT", "物联网"], ["XJ", "校交"], ["ZY", "卓越(创新)"], ["BD", "大数据"], ["IST", "智能"]]);
const dataset = ref<listItem[][]>([]);

const getData = () => {
	fetchEachGradeNumber().then((res) => {
		const data = ref<listItem[]>([]);
		const gradeList: string[] = []
		const majorSet: Set<string> = new Set()
		data.value = res.data.data;
		data.value.sort(((a, b) => { return Number(a.grade) - Number(b.grade) }))
		for (var item in data.value) {
			gradeList.push(data.value[item].grade);
			data.value[item].major.sort((a, b) => { return b.value - a.value })
			for (var i in data.value[item].major) {
				majorSet.add(data.value[item].major[i].key)
				data.value[item].major[i].key = majorMap.get(data.value[item].major[i].key)!
			}
		}
		for (let i = 0; i < data.value.length; i += 2)
			dataset.value.push(data.value.slice(i, i + 2));
		localStorage.setItem("gradeList", JSON.stringify(gradeList))
		const majorList: string[] = Array.from(majorSet)
		localStorage.setItem("majorList", JSON.stringify(majorList))
	})
	
};
getData();


</script>

<style scoped>
:deep(.el-progress-bar__innerText) {
	color: black ;
}

.el-row {
	margin-bottom: 20px;
}

.grid-content {
	display: flex;
	align-items: center;
	height: 100px;
}

.grid-cont-right {
	flex: 1;
	text-align: center;
	font-size: 14px;
	color: #999;
}

.grid-num {
	font-size: 30px;
	font-weight: bold;
}

.grid-con-icon {
	font-size: 50px;
	width: 100px;
	height: 100px;
	text-align: center;
	line-height: 100px;
	color: #fff;
}

.grid-con-1 .grid-con-icon {
	background: rgb(45, 140, 240);
}

.grid-con-1 .grid-num {
	color: rgb(45, 140, 240);
}

.grid-con-2 .grid-con-icon {
	background: rgb(100, 213, 114);
}

.grid-con-2 .grid-num {
	color: rgb(100, 213, 114);
}

.grid-con-3 .grid-con-icon {
	background: rgb(242, 94, 67);
}

.grid-con-3 .grid-num {
	color: rgb(242, 94, 67);
}

.user-info {
	display: flex;
	align-items: center;
	padding-bottom: 20px;
	border-bottom: 2px solid #ccc;
	margin-bottom: 20px;
}

.user-info-cont {
	padding-left: 50px;
	flex: 1;
	font-size: 14px;
	color: #999;
}

.user-info-cont div:first-child {
	font-size: 30px;
	color: #222;
}

.user-info-list {
	font-size: 14px;
	color: #999;
	line-height: 25px;
}

.user-info-list span {
	margin-left: 70px;
}

.mgb20 {
	margin-bottom: 20px;
}

.todo-item {
	font-size: 14px;
}

.todo-item-del {
	text-decoration: line-through;
	color: #999;
}

.schart {
	width: 100%;
	height: 300px;
}
</style>
