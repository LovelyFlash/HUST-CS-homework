<template>
	<div>
		<el-drawer class="my_drawer" v-model="table" direction="rtl" size="50%">
			<template #title>
				<div class="drawer_title">
					<span>{{ drawerTitle }}</span>
					<el-icon class="my_download" @click="downloadFile">
						<download />
					</el-icon>
				</div>
			</template>
			<el-table :data="gridData">
				<el-table-column property="order" label="序号" width="150" />
				<el-table-column property="grade" label="班级" width="150" />
				<el-table-column property="stuNum" label="学号" width="200" />
				<el-table-column property="stuName" label="姓名" />
			</el-table>
		</el-drawer>
		<div class="container">
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
			<!-- <div class="handle-box" style="display: none;">
				<el-select
					v-model="courseName"
					placeholder="请选择课程"
					clearable
					class="handle-select mr10"
					@change="$forceUpdate()"
					@clear="clearCourses">
					<el-option
						v-for="course in coursesData"
						:key="course.label"
						:value="course.value">
					</el-option>
				</el-select>
				<el-button
					type="primary"
					:icon="Search"
					@click="handleSearchCourse(courseName)"
					>搜索</el-button
				>
			</div> -->
			<div class="handle-box">
				<el-select
					v-model="major"
					class="handle-select mr10"
					@change="
						$forceUpdate();
						chooseMajor();
					">
					<template v-for="item in majorList" :key="item.value">
						<el-option :label="item.label" :value="item"></el-option>
					</template>
				</el-select>
			</div>
			<div class="quickCourses">
				<el-radio-group v-model="radioCourse" @change="chooseCourse">
					<el-radio
						:label="course.label"
						v-for="course in coursesData"
						:key="course.label"
						class="myradio"
						>{{ course.value }}</el-radio
					>
				</el-radio-group>
			</div>
			<div>
				<el-table
					:data="tableData"
					border
					class="table"
					ref="multipleTable"
					:row-style="{ height: '500px' }"
					:header-cell-style="{ textAlign: 'center' }"
					:cell-style="{ textAlign: 'center' }">
					<!-- <el-table-column prop="id" label="ID" width="55" align="center"></el-table-column> -->
					<el-table-column prop="courseName" label="课程名称" width="140">
						<template #default="scope">
							({{ scope.row.major }})<br />
							{{ scope.row.courseName }}
							<p class="fail_text">（共计{{ scope.row.sumFailedNums }}人次）</p>
							<el-button
								type="primary"
								bg
								@click="
									openDrawer(scope.row.courseName, scope.row.failStudentsList)
								"
								>挂科学生详情</el-button
							>
						</template>
					</el-table-column>
					<el-table-column label="考试通过情况">
						<template #default="scope">
							<CourseBar :chartData="scope.row" />
						</template>
					</el-table-column>
					<el-table-column label="分数分段情况">
						<template #default="scope">
							<CourseLine :chartData="scope.row" />
						</template>
					</el-table-column>
				</el-table>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts" name="basetable">
import { ref, reactive, onMounted } from "vue";
import { ElDrawer, ElMessage, ElMessageBox } from "element-plus";
import { Download } from "@element-plus/icons";
import { Delete, Edit, Search, Plus } from "@element-plus/icons-vue";
import { fetchData, fetchCoursesData, downloadCoursesData } from "../api/index";
import CourseBar from "../components/courseBar.vue";
import CourseLine from "../components/courseLine1.vue";
import fileDownload from "js-file-download";
import { List, number } from "echarts";

interface TableItem {
	courseName: string;
	major: string;
	failed_nums: string;
	gradeDistribute: string;
	id: string;
	pass_rate: string;
	sumFailedNums: string;
}
interface ListItem {
	value: string;
	label: string;
}
interface GridItem {
	order: number;
	grade: string;
	stuNum: string;
	stuName: string;
}

const query = reactive({
	address: "",
	name: "",
	pageIndex: 1,
	pageSize: 10,
});
let term = "11";
let major = ref<ListItem>({ value: "ALL", label: "全部" });
const majorList = ref<ListItem[]>([]);
const radioCourse = ref("");
const courseName = ref("");
const tableData = ref<TableItem[]>([]);
const tableDataCopy = ref<TableItem[]>([]);
let coursesData = ref<ListItem[]>([]);

const table = ref(false);
const drawerTitle = ref("");
const gridData = ref<GridItem[]>([]); //不及格学生表信息

const majorMap = new Map<string, string>([
	["ALL", "全部"],
	["CS", "计算机"],
	["TL", "图灵"],
	["ACM", "ACM"],
	["BSB", "本硕博(启明)"],
	["IOT", "物联网"],
	["XJ", "校交"],
	["ZY", "卓越(创新)"],
	["BD", "大数据"],
	["IST", "智能"]
]);

onMounted(() => {
	getData(term);
});
// 获取表格数据
const getData = (term: String) => {
	fetchCoursesData(term).then((res) => {
		courseName.value = "";
		tableData.value = [];
		tableDataCopy.value = res.data.data;
		coursesData.value = [];
		var coursesCount = 0;
		for (var key in tableDataCopy.value) {
			var addItem: ListItem = {
				value: tableDataCopy.value[key].courseName,
				label: tableDataCopy.value[key].courseName,
			};
			if (
				coursesCount == 0 ||
				coursesData.value[coursesCount - 1].value != addItem.value
			) {
				coursesData.value.push(addItem);
				coursesCount += 1;
			}
		}

		var majorSet = new Set<any>();
		majorList.value = [];
		for (var key in tableDataCopy.value)
			if (!majorSet.has(tableDataCopy.value[key].major)) {
				majorSet.add(tableDataCopy.value[key].major);
				majorList.value.push({
					value: tableDataCopy.value[key].major,
					label: majorMap.get(tableDataCopy.value[key].major)!,
				});
			}
		majorList.value = majorList.value.sort();
		major.value = { value: "ALL", label: "全部" };

		radioCourse.value = '';
	});
};

// 查询操作
const handleSearchTerm = (term: String) => {
	// 根据学期搜索
	getData(term);
};
const handleSearchCourse = (courseName: String) => {
	// 根据课程名称搜索
	// console.log('course:' + courseName);
	// console.log(tableData.value);
	// console.log(tableDataCopy.value);
	console.log(courseName);
	radioCourse.value = "";

	tableData.value = tableDataCopy.value;
	tableData.value = tableData.value.filter((item) => {
		return item.courseName == courseName && item.major == major.value.value;
	});
};

const chooseCourse = () => {
	// 选择某个课程
	console.log(radioCourse.value);
	// showTable.value = true;
	courseName.value = "";
	tableData.value = tableDataCopy.value;
	tableData.value = tableData.value.filter((item) => {
		return (
			item.courseName == radioCourse.value && item.major == major.value.value
		);
	});
};

const chooseMajor = () => {
	// if (radioCourse.value == "")
	// 	handleSearchCourse(courseName.value)
	// else
	chooseCourse();
};

const openDrawer = (val: string, failStudentsList: any) => {
	// 点击打开抽屉
	table.value = true;
	console.log(failStudentsList);
	gridData.value = [];
	failStudentsList.forEach((el: any, index: number) => {
		// console.log(el, index);
		let tempStu: GridItem = {
			order: index + 1,
			grade: el[0],
			stuNum: el[1],
			stuName: el[2],
		};
		gridData.value.push(tempStu);
	});
	console.log(gridData.value);
	drawerTitle.value = "《" + val + "》挂科同学详情";
};

const downloadFile = () => {
	let courseName = "";
	courseName = drawerTitle.value.split("《")[1].split("》")[0];
	console.log(courseName);
	downloadCoursesData({courseName: courseName}).then((res) => {
		console.log(res);
		if (res.status == 200) {
			fileDownload(res.data, "failed_students_" + courseName + ".xlsx");
			ElMessage.success({
				message: "文件下载成功！",
				type: "success",
			});
		} else {
			ElMessage.error("文件下载失败！");
		}
	});
};

// // 删除操作
// const handleDelete = (index: number) => {
// 	// 二次确认删除
// 	ElMessageBox.confirm('确定要删除吗？', '提示', {
// 		type: 'warning'
// 	})
// 		.then(() => {
// 			ElMessage.success('删除成功');
// 			tableData.value.splice(index, 1);
// 		})
// 		.catch(() => {});
// };

// // 表格编辑时弹窗和保存
// const editVisible = ref(false);
// let form = reactive({
// 	name: '',
// 	address: ''
// });
// let idx: number = -1;
// const handleEdit = (index: number, row: any) => {
// 	idx = index;
// 	form.name = row.name;
// 	form.address = row.address;
// 	editVisible.value = true;
// };
// const saveEdit = () => {
// 	editVisible.value = false;
// 	ElMessage.success(`修改第 ${idx + 1} 行成功`);
// 	tableData.value[idx].name = form.name;
// 	tableData.value[idx].address = form.address;
// };
</script>

<style scoped>
.drawer_title {
	display: flex;
	align-items: center;
}

.drawer_title i.el-icon {
	background: rgb(120, 185, 236);
	color: white;
	font-weight: 700;
	border-radius: 50%;
	display: inline-block;
	width: 30px;
	height: 30px;
	line-height: 30px;
	text-align: center;
	font-size: 24px;
	margin-left: 20px;
}
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
.myradio {
	width: 25%;
}
</style>
