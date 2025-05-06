<template style="height: 100%;">
	<div style="height: 100%;">
		<div class="container" style="height: 90%;">
			<div class="handle-box">
				<el-select
					v-model="term"
					placeholder="请选择学期"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<el-option key="11" label="第一学年·第一学期" value="11"></el-option>
					<el-option key="12" label="第一学年·第二学期" value="12"></el-option>
					<el-option key="21" label="第二学年·第一学期" value="21"></el-option>
					<el-option key="22" label="第二学年·第二学期" value="22"></el-option>
					<el-option key="31" label="第三学年·第一学期" value="31"></el-option>
					<el-option key="32" label="第三学年·第二学期" value="32"></el-option>
					<el-option key="41" label="第四学年·第一学期" value="41"></el-option>
					<el-option key="42" label="第四学年·第二学期" value="42"></el-option>
				</el-select>
				<el-button type="primary" :icon="Search" @click="handleSearchTerm(term)"
					>搜索</el-button
				>
			</div>
			<el-table
				:data="dataset"
				border
				class="table"
				ref="multipleTable"
				:row-style="{ height: '500px' }"
				:header-cell-style="{ textAlign: 'center' }"
				:cell-style="{ textAlign: 'center' }"
				style="height: 93%">
				<el-table-column prop="courseName" label="年级" width="9.5%">
					<template #default="scope" class="template">
						20{{ scope.row[0].grade }}级
					</template>
				</el-table-column>
				<el-table-column label="专业挂科情况" width="42%">
					<template #default="scope" class="template">
						<ClassBar :chartData="scope.row[0]" />
					</template>
				</el-table-column>
				<el-table-column label="各班挂科情况" width="80%">
					<template #default="scope" class="template">
						<ClassBar :chartData="scope.row[1]" />
					</template>
				</el-table-column>
			</el-table>
		</div>
	</div>
</template>

<script setup lang="ts" name="basetable">
import { ref, reactive } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Delete, Edit, Search, Plus } from "@element-plus/icons-vue";
import { fetchData, fetchClassesData } from "../api/index";
import ClassBar from "../components/classBar.vue";

interface TableItem {
	classNameList: String[];
	failedNum: number[];
	failedRate: number[];
	grade: string;
	term: string;
	type: number;
}
interface ListItem {
	value: string;
	label: string;
}

const query = reactive({
	address: "",
	name: "",
	pageIndex: 1,
	pageSize: 10,
});
let term = "11";
const tableData = ref<TableItem[]>([]);
const classData = ref<TableItem[]>([]);
const majorData = ref<TableItem[]>([]);
const dataset = ref<TableItem[][]>([]);

// 获取表格数据
const getData = (term: String) => {
	fetchClassesData(term).then((res) => {
		tableData.value = res.data.data;
		console.log(tableData.value);
		tableData.value.sort((a, b) => {
			return Number(a.grade) - Number(b.grade);
		});
		classData.value = [];
		majorData.value = [];
		for (var item in tableData.value)
			if (tableData.value[item].type == 0)
				majorData.value.push(tableData.value[item]);
			else classData.value.push(tableData.value[item]);
		dataset.value = [];
		for (var item in classData.value)
			dataset.value.push([majorData.value[item], classData.value[item]]);
	});
};
getData(term);

// 查询操作
const handleSearchTerm = (term: String) => {
	console.log("term:" + term);
	getData(term);
};
</script>

<style scoped>
.handle-box {
	display: inline-block;
	margin-bottom: 20px;
	margin-right: 50px;
}

.handle-select {
	width: 200px;
}

.handle-input {
	width: 300px;
}

.table {
	width: 100%;
	font-size: 14px;
}

.red {
	color: #ff0000;
}

.mr10 {
	margin-right: 10px;
}

.table-td-thumb {
	display: block;
	margin: auto;
	width: 40px;
	height: 40px;
}

.fail_text {
	color: #ff0000;
	font-size: 10px;
}

:deep(.el-table__header)  {
	width: 100% !important;
}

:deep(.el-table__body)  {
	width: 100% !important;
}
</style>
