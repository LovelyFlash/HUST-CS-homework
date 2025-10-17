<template style="height: 100%;">
	<div style="height: 100%;">
		<div class="container" style="height: 92%;">
			<el-table
				:data="tableData"
				border
				class="table"
				ref="multipleTable"
				:row-style="{ height: '500px' }"
				:header-cell-style="{ textAlign: 'center' }"
				:cell-style="{ textAlign: 'center' }"
				style="height: 93%">
				<el-table-column prop="courseName" label="专业" width="10%">
					<template #default="scope" class="template">
						{{ scope.row.major }}
					</template>
				</el-table-column>
				<el-table-column label="各年级挂科情况" width="75%">
					<template #default="scope" class="template">
						<MajorBar1 :chartData="scope.row" />
					</template>
				</el-table-column>
				<el-table-column label="各学期挂科情况" width="90%">
					<template #default="scope" class="template">
						<MajorBar :chartData="scope.row" />
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
import { fetchData, fetchClassesData, fetchMajorData } from "../api/index";
import MajorBar from "../components/majorBar.vue";
import MajorBar1 from "../components/majorBar1.vue";

interface TableItem {
	major: String,
    gradeNameList: String[],
    gradeFailedNum: number[],
    gradeFailedRate: number[],
    gradeTotalNum: number[],
    classNameList: String[],
    failedNum: number[],
    failedRate: number[],
    totalNum: number[],
    showLabel: number[],

}

const tableData = ref<TableItem[]>([]);
const majorMap = new Map<string, string>([
	["ALL", "全部"],
	["CS", "计算机"],
	["ACM", "ACM"],
	["BSB", "本硕博(启明)"],
	["IOT", "物联网"],
	["XJ", "校交"],
	["ZY", "卓越(创新)"],
	["BD", "大数据"],
	["IST", "智能"]
]);
// 获取表格数据
const getData = () => {
	fetchMajorData().then((res) => {
		// console.log(res);

		tableData.value = res.data.data;
		for (var i = 0; i < tableData.value.length; i++)
			tableData.value[i].major = majorMap.get(tableData.value[i].major.toString())!;
		console.log(tableData.value);
	});
};
getData();


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
