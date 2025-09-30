<template>
	<div class="container">
		<el-row>
			<el-col :span="8">
				班级成绩单及个人成绩单:
				<el-upload
					class="upload-demo"
					drag
					action="proxy/apis/v1/uploadFile"
					:auto-upload="false"
					v-model:file-list="fileList"
					accept=".xlsx"
					multiple
					ref="uploadRef"
				>
					<el-icon class="el-icon--upload"><upload-filled /></el-icon>
					<div class="el-upload__text">
					将文件拖到此处，或<em>点击上传</em>
					<br />
					班级成绩单请按格式重命名，例:CS2201S11<br/>
					指CS2201班在第一学年上半学期成绩
					</div>
					<template #tip>
					<div class="el-upload__tip">
						上传的文件列表如下：
					</div>
					</template>
				</el-upload>
				<el-button class="ml-3" type="success" @click="submitUpload">
				确定上传
				</el-button>
				<el-button class="ml-3" style="color: green" @click="dataReduct">
				数据整理(全部)
				</el-button>
				<el-button class="ml-3" style="color: green" @click="dataReductPersonal">
				数据整理(仅个人)
				</el-button>
			</el-col>
			<el-col :span="8">
				课程分类表格:
				<el-upload
					class="upload-demo"
					drag
					action="proxy/apis/v1/uploadCourseFile"
					:auto-upload="false"
					v-model:file-list="courseFileList"
					accept=".xlsx"
					multiple
					ref="uploadCourseRef"
				>
					<el-icon class="el-icon--upload"><upload-filled /></el-icon>
					<div class="el-upload__text">
					将文件拖到此处，或<em>点击上传</em>
					<br />
					先将课程文件导出，再进行修改并上传<br/>
					若有问题可尝试重置数据重新上传
					</div>
					<template #tip>
					<div class="el-upload__tip">
						上传的文件列表如下：
					</div>
					</template>
				</el-upload>
				<el-button class="ml-3" type="primary" @click="downloadCourse">
				课程导出
				</el-button>
				<el-button class="ml-3" type="success" @click="submitUploadCourse">
				确定上传
				</el-button>
				<el-button class="ml-3" style="color: green" @click="courseCalc">
				数据整理(仅分类)
				</el-button>
			</el-col>
			<el-col :span="7">
				平均分表格:
				<el-upload
					class="upload-demo"
					drag
					action="proxy/apis/v1/uploadScoreFile"
					:auto-upload="false"
					v-model:file-list="scoreFileList"
					accept=".xlsx"
					multiple
					ref="uploadScoreRef"
				>
					<el-icon class="el-icon--upload"><upload-filled /></el-icon>
					<div class="el-upload__text">
					将文件拖到此处，或<em>点击上传</em>
					<br />
					<br/>
					仅上传平均分表格,无需重命名
					</div>
					<template #tip>
					<div class="el-upload__tip">
						上传的文件列表如下：
					</div>
					</template>
				</el-upload>
				<el-button class="ml-3" type="success" @click="submitUploadScore">
				确定上传
				</el-button>
				<el-button class="ml-3" style="color: green" @click="scoreCalc">
				数据整理(仅平均分)
				</el-button>
			</el-col>
		</el-row>
		<el-row style="margin-top: 20px;">
			<el-col :span="18"></el-col>
			<el-col :span="6">
				<el-button class="ml-3" style="color: grey" @click="clearCalculate">
				清除预处理数据
				</el-button>
				<el-button type="danger" color="red" @click="flushALLData">删除全部数据</el-button>
			</el-col>
		</el-row>
	</div>
	<div class="container">
		<el-row style="height: 50px; font-size: 20px;">优良学风班</el-row>
		<el-row style="color: #1f2f3d; font-size: 16px;">
			<el-col :span="3" style="text-align: center;">年级</el-col>
			<el-col :span="3" style="text-align: center;">第一学年</el-col>
			<el-col :span="3" style="text-align: center;">第二学年</el-col>
			<el-col :span="3" style="text-align: center;">第三学年</el-col>
			<el-col :span="3" style="text-align: center;">班级总数</el-col>
			<el-col :span="1" style="text-align: center;"></el-col>
		</el-row>
		<el-row style="color: #1f2f3d; font-size: 16px;">
			<!-- <el-col :span="3" style="text-align: center;">
				<el-select
					v-model="grade"
					placeholder="请选择年级"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<template v-for="gradeIndex in gradeList">
						<el-option
							:label="'20' + gradeIndex + '级'"
							:value="gradeIndex"></el-option>
					</template>
				</el-select>
			</el-col> -->
			<el-col :span="3" style="text-align: center;"><el-input style="width: 75%;" placeholder="填年级的后两位" v-model="grade"></el-input></el-col>
			<el-col :span="3" style="text-align: center;"><el-input style="width: 75%;" placeholder="无,则不填" v-model="year1"></el-input></el-col>
			<el-col :span="3" style="text-align: center;"><el-input style="width: 75%;" placeholder="无,则不填" v-model="year2"></el-input></el-col>
			<el-col :span="3" style="text-align: center;"><el-input style="width: 75%;" placeholder="无,则不填" v-model="year3"></el-input></el-col>
			<el-col :span="3" style="text-align: center;"><el-input style="width: 75%;" placeholder="无,则不填" v-model="totalClassNum"></el-input></el-col>
			<el-col :span="2" style="text-align: center;"><el-button type="info" @click="reset">复位</el-button></el-col>
			<el-col :span="2" style="text-align: center;"><el-button type="primary" @click="commitExcellent">上传</el-button></el-col>
			<el-col :span="1"></el-col>
			<el-col :span="4" style="text-align: right;"><el-button type="danger" color="red" @click="flushALL">删除全部数据</el-button></el-col>
		</el-row>

	</div>
	<div class="container">
		<el-row style="height: 50px; font-size: 20px;">学分相关</el-row>
		<el-row style="color: #1f2f3d; font-size: 16px;">
			<el-col :span="3" style="text-align: center;">年级</el-col>
			<el-col :span="3" style="text-align: center;">专业</el-col>
			<el-col :span="3" style="text-align: center;">红牌比例</el-col>
			<el-col :span="3" style="text-align: center;">黄牌比例</el-col>
			<el-col :span="4" style="text-align: center;">应修学分(不含公共选修)</el-col>
			<el-col :span="4" style="text-align: center;">应修学分(含公共选修)</el-col>
			<el-col :span="4" style="text-align: center;"></el-col>
		</el-row>
		<el-row style="color: #1f2f3d; font-size: 16px;">
			<el-col :span="3" style="text-align: center;">
				<el-select
					v-model="gradeForInfo"
					placeholder="请选择年级"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<template v-for="gradeIndex in gradeList">
						<el-option
							:label="'20' + gradeIndex + '级'"
							:value="gradeIndex"></el-option>
					</template>
				</el-select>
			</el-col>
			<el-col :span="3" style="text-align: center;">
				<el-select
					v-model="major"
					placeholder="请选择专业"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<template v-for="majorItem in majorList">
						<el-option
							:label="majorItem.label"
							:value="majorItem.value"></el-option>
					</template>
				</el-select>
			</el-col>
			<el-col :span="3" style="text-align: center;"><el-input style="width: 75%;" placeholder="填0~1的浮点数" v-model="redRate"></el-input></el-col>
			<el-col :span="3" style="text-align: center;"><el-input style="width: 75%;" placeholder="填0~1的浮点数" v-model="yellowRate"></el-input></el-col>
			<el-col :span="4" style="text-align: center;"><el-input style="width: 75%;" placeholder="填浮点数" v-model="requiredCreditExcludePublicElective"></el-input></el-col>
			<el-col :span="4" style="text-align: center;"><el-input style="width: 75%;" placeholder="填浮点数" v-model="requiredCreditIncludePublicElective"></el-input></el-col>
			<el-col :span="2" style="text-align: center;"><el-button type="info" @click="resetInfo">复位</el-button></el-col>
			<el-col :span="2" style="text-align: center;"><el-button type="primary" @click="setStudentInfo">上传</el-button></el-col>
		</el-row>

	</div>
</template>

<script setup lang="ts">
import { fi } from "element-plus/es/locale";
import {ref, onMounted} from "vue"
import type { UploadUserFile, UploadRawFile, UploadInstance  } from 'element-plus'
import { dateEquals, ElMessage, ElMessageBox } from 'element-plus'
import type { Action } from 'element-plus'
import {toRaw} from '@vue/reactivity'
import {dataReduction, dataReductionPersonal, uploadExcellentClassData, flushALLExcellent, downloadCourseFile, courseCalculate, scoreCalculate, setStudentInfoConfig, flushALLDatabase, clearCalculateData} from '../api/index'
import { Message } from "@element-plus/icons-vue";
import fileDownload from "js-file-download";

const fileList = ref<UploadUserFile[]>([])
const courseFileList = ref<UploadUserFile[]>([])
const scoreFileList = ref<UploadUserFile[]>([])
const uploadRef = ref<UploadInstance>()
const uploadCourseRef = ref<UploadInstance>()
const uploadScoreRef = ref<UploadInstance>()
const grade = ref<string>('')
const year1 = ref<string>('')
const year2 = ref<string>('')
const year3 = ref<string>('')
const totalClassNum = ref<string>('')
const gradeList = ref<string[]>([]);
const gradeForInfo = ref<string>("");
const major = ref<string>("");
const majorList = ref<listItem[]>([])
const redRate = ref<string>("");
const yellowRate = ref<string>("");
const requiredCreditExcludePublicElective = ref<string>("");
const requiredCreditIncludePublicElective = ref<string>("");
const majorMap = new Map<string, string>([["ALL", "全部"],	["TL", "图灵"], ["CS", "计算机"], ["ACM", "ACM"], ["BSB", "本硕博(启明)"], ["IOT", "物联网"], ["XJ", "校交"], ["ZY", "卓越(创新)"], ["BD", "大数据"], ["IST", "智能"]]);

interface uploadExcellent {
	grade: number;
	year: number;
	excellentClassNum: number;
}

interface listItem {
	label: string;
	value: string;
}

const getGradeList = () => {
	gradeList.value = JSON.parse(localStorage.getItem("gradeList")!);
	gradeList.value.sort((a, b) => {
		return Number(a) - Number(b);
	});
};

getGradeList();

const getMajorList = () => {
	const majorArray = JSON.parse(localStorage.getItem("majorList")!);
	majorList.value = []
	for (var i in majorArray) {
		majorList.value.push({ label: majorMap.get(majorArray[i])!, value: majorArray[i]})
	}
	majorList.value.sort((a, b) => {
		return Number(a.value) - Number(b.value);
	});
	major.value = "";
};

getMajorList();

const reset = () => {
	grade.value = '';
	year1.value = '';
	year2.value = '';
	year3.value = '';
	totalClassNum.value = '';
};

const resetInfo = () => {
	gradeForInfo.value = '';
	major.value = '';
	redRate.value = '';
	yellowRate.value = '';
	requiredCreditExcludePublicElective.value = '';
	requiredCreditIncludePublicElective.value = '';
};

const setStudentInfo = () => {
	if (gradeForInfo.value == '' || major.value == '' ||redRate.value == '' || yellowRate.value == '' || requiredCreditExcludePublicElective.value == '' || requiredCreditIncludePublicElective.value == '' || Number(redRate.value) < 0.0 || Number(redRate.value) > 1.0 || Number(yellowRate.value) < 0.0 || Number(yellowRate.value) > 1.0 || Number(requiredCreditExcludePublicElective.value) < 0.0 || Number(requiredCreditIncludePublicElective.value) < 0.0) {
		ElMessage.warning({ message: "格式错误" });
		return;
	}
	else
	{
		setStudentInfoConfig({ grade: gradeForInfo.value, major: major.value, redRate: Number(redRate.value), yellowRate: Number(yellowRate.value), requiredCreditExcludePublicElective: Number(requiredCreditExcludePublicElective.value), requiredCreditIncludePublicElective: Number(requiredCreditIncludePublicElective.value) }).then((res) => {
			console.log(res)
			ElMessage.success({message: "上传成功"})
		})
	}
}

const downloadCourse = async () => {
	for (var i in gradeList.value)
	{
		console.log(gradeList.value[i])
		await downloadCourseFile(gradeList.value[i]).then((res) => {
			fileDownload(res.data, gradeList.value[i] + "_grade_course.xlsx")
		})
	}
}

const courseCalc = () => {
	ElMessageBox.confirm(
		'大概需要2-3分钟!',
		'数据整理(课程分类)',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		courseCalculate().then(res => { console.log(res) });
		ElMessage({
			type: 'info',
			message: '请耐心等待',
		})
	})
}

const scoreCalc = () => {
	ElMessageBox.confirm(
		'大概需要1-2分钟!',
		'数据整理(平均分)',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		scoreCalculate().then(res => { console.log(res) });
		ElMessage({
			type: 'info',
			message: '请耐心等待',
		})
	})
}

const clearCalculate = () => {
	clearCalculateData();
	ElMessage.success({message: "清除完成"})
}

const flushALLData = () => {
	ElMessageBox.confirm(
		'包括数据库内的全部数据和上传的所有文件(成绩文件和课程分类文件,建议先备份),但不包括优良学风班数据和红黄牌标准数据',
		'删除数据',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		flushALLDatabase();
		ElMessage({
			type: 'success',
			message: '删除成功！',
		})
	})
}

const flushALL = () => {
	ElMessageBox.confirm(
		"是否删除全部优良学风班数据?",
		'删除数据',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		flushALLExcellent();
		ElMessage({
			type: 'success',
			message: '删除成功！',
		})
	})
}

const commitExcellent = () => {
	if (Number(grade.value) <= 0 || Number(grade.value) > 99 || (! /^\d+$/.test(grade.value)))
	{
		ElMessage.warning({ message: "年级格式错误" });
		return
	}
	if (totalClassNum.value == '' || (! /^\d+$/.test(totalClassNum.value)) || totalClassNum.value == '') {
		ElMessage.warning({ message: "班级总数格式错误" });
		return
	}
	const uploadList: { grade: number; year: number; excellentClassNum: number; totalClassNum: number}[] = [];
	if (year1.value != '' && /^\d+$/.test(year1.value))
		uploadList.push({ grade: Number(grade.value), year: Number(grade.value) + 2001, excellentClassNum: Number(year1.value), totalClassNum: Number(totalClassNum.value)})
	else if (year1.value != '') {
		ElMessage.warning({ message: "第一学年格式错误" });
		return
	}
	if (year2.value != '' && /^\d+$/.test(year2.value))
		uploadList.push({ grade: Number(grade.value), year: Number(grade.value) + 2002, excellentClassNum: Number(year2.value), totalClassNum: Number(totalClassNum.value) })
	else if (year2.value != '') {
		ElMessage.warning({ message: "第二学年格式错误" });
		return
	}
	if (year3.value != '' && /^\d+$/.test(year3.value))
		uploadList.push({ grade: Number(grade.value), year: Number(grade.value) + 2003, excellentClassNum: Number(year3.value), totalClassNum: Number(totalClassNum.value) })
	else if (year3.value != '') {
		ElMessage.warning({ message: "第三学年格式错误" });
		return
	}
	
	if (JSON.stringify(uploadList) == '[]') {
		ElMessage.warning({ message: "无上传内容" });
		return
	}
	ElMessageBox.confirm(
		"上传列表: " + JSON.stringify(uploadList),
		'上传优良学风班',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(async () => {
		let success: number = 0, failed: number = 0;
		for (var i in uploadList) {
			await uploadExcellentClassData(uploadList[i]).then((res) => {
				console.log(res)
				if (res.data.code == 200)
					success += 1;
				else
					failed += 1;
			})
		}
		ElMessageBox.alert("成功 " + success + " 个,已有 " + failed + " 个.")
	}).catch(() => {
		ElMessage({
			type: 'info',
			message: '取消上传！',
		})
    })
}

const submitUpload = () => { // 确定上传按钮点击事件
	console.log(fileList.value);
	let fileNames:string = "";
	fileList.value.forEach((el:any) => {
		fileNames += '<p>' + el.name + '</p>';
	})
	fileNames += '<p>'+"确定上传这些文件吗？"+'</p>';
	console.log(fileNames);
	ElMessageBox.confirm(
		fileNames,
		'上传文件',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		uploadRef.value!.submit();
		ElMessage({
			type: 'success',
			message: '文件上传成功！',
		})
		uploadRef.value!.clearFiles();
	}).catch(() => {
		ElMessage({
			type: 'info',
			message: '取消上传文件！',
		})
    })
}

const submitUploadCourse = () => { // 确定上传按钮点击事件
	console.log(courseFileList.value);
	let fileNames:string = "";
	courseFileList.value.forEach((el:any) => {
		fileNames += '<p>' + el.name + '</p>';
	})
	fileNames += '<p>'+"确定上传这些文件吗？"+'</p>';
	console.log(fileNames);
	ElMessageBox.confirm(
		fileNames,
		'上传文件',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		uploadCourseRef.value!.submit();
		ElMessage({
			type: 'success',
			message: '文件上传成功！',
		})
		uploadCourseRef.value!.clearFiles();
	}).catch(() => {
		ElMessage({
			type: 'info',
			message: '取消上传文件！',
		})
    })
}

const submitUploadScore = () => { // 确定上传按钮点击事件
	console.log(scoreFileList.value);
	let fileNames:string = "";
	scoreFileList.value.forEach((el:any) => {
		fileNames += '<p>' + el.name + '</p>';
	})
	fileNames += '<p>'+"确定上传这些文件吗？"+'</p>';
	console.log(fileNames);
	ElMessageBox.confirm(
		fileNames,
		'上传文件',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		uploadScoreRef.value!.submit();
		ElMessage({
			type: 'success',
			message: '文件上传成功！',
		})
		uploadScoreRef.value!.clearFiles();
	}).catch(() => {
		ElMessage({
			type: 'info',
			message: '取消上传文件！',
		})
    })
}

const dataReduct = () => {
	ElMessageBox.confirm(
		'大概需要3-5分钟!',
		'数据整理(全部)',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		dataReduction().then(res => { console.log(res) });
		ElMessage({
			type: 'info',
			message: '请耐心等待',
		})
	})
}

const dataReductPersonal = () => {
	ElMessageBox.confirm(
		'大概需要3-5分钟!',
		'数据整理(仅个人)',
		{
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		dangerouslyUseHTMLString: true,
		}
	).then(() => {
		dataReductionPersonal().then(res => { console.log(res) });
		ElMessage({
			type: 'info',
			message: '请耐心等待',
		})
	})
}

</script>

<style scoped>
.content-title {
	font-weight: 400;
	line-height: 50px;
	margin: 10px 0;
	font-size: 22px;
	color: #1f2f3d;
}

.pre-img {
	width: 100px;
	height: 100px;
	background: #f8f8f8;
	border: 1px solid #eee;
	border-radius: 5px;
}
.crop-demo {
	display: flex;
	align-items: flex-end;
}
.crop-demo-btn {
	position: relative;
	width: 100px;
	height: 40px;
	line-height: 40px;
	padding: 0 20px;
	margin-left: 30px;
	background-color: #409eff;
	color: #fff;
	font-size: 14px;
	border-radius: 4px;
	box-sizing: border-box;
}
.crop-input {
	position: absolute;
	width: 100px;
	height: 40px;
	left: 0;
	top: 0;
	opacity: 0;
	cursor: pointer;
}

.excellent-flushall {
	background-color: rgba(193, 69, 69, 0.956);
	color: black;
}

</style>
