<template style="height: 100%;">
	<div style="height: 100%;">
		<div class="container" style="height: 90%;">
			<div class="handle-box">
				<el-select
					v-model="term"
					placeholder="请选择学期"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<el-option key="ALL" label="全部学年·全部学期" value="ALL"></el-option>
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
			<div class="handle-box">
				<el-select
					v-model="grade"
					placeholder="请选择年级"
					class="handle-select mr10"
					@change="$forceUpdate(); changeGrade();">
					<template v-for="gradeIndex in gradeList">
						<el-option
							:label="'20' + gradeIndex + '级'"
							:value="gradeIndex"></el-option>
					</template>
				</el-select>
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
				<el-table-column prop="major" label="专业" width="9.5%">
				</el-table-column>
				<el-table-column label="平均成绩分布" width="80%">
					<template #default="scope" class="template">
						<ScoreBar :chartData="scope.row.info" />
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
import { fetchData, fetchScoreData } from "../api/index";
import ScoreBar from "../components/scoreBar.vue";

interface InfoItem {
	Name: string;
	ID: string;
	Score: number;
	Index: number;
	Class: number;
}

interface TableItem {
	grade: string;
	term: string;
	major: string;
	info: InfoItem;
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
let term = "ALL";
let grade = ref<string>("");
const tableData = ref<TableItem[]>([]);
const gradeList = ref<string[]>([]);
const dataset = ref<TableItem[]>([]);

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

const getGradeList = () => {
	gradeList.value = JSON.parse(localStorage.getItem("gradeList")!);
	gradeList.value.sort((a, b) => {
		return Number(a) - Number(b);
	});
};

getGradeList();

// 获取表格数据
const getData = (term: String) => {
	fetchScoreData(term).then((res) => {
		tableData.value = res.data.data;
		// console.log(tableData.value);
		tableData.value.sort((a, b) => {
			return Number(a.grade) - Number(b.grade);
		});
		for (var i = 0; i < tableData.value.length; i++)
			tableData.value[i].major = majorMap.get(tableData.value[i].major.toString())!;
	});
};
getData(term);

// 查询操作
const handleSearchTerm = (term: String) => {
	console.log("term:" + term);
	getData(term);
	grade.value = "";
	console.log(dataset.value)
};

const changeGrade = () => {
	dataset.value = tableData.value.filter((item) => {
		return item.grade == grade.value;
	})
	console.log(dataset.value)
}
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
