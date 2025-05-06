import { data } from "jquery";
import request from "../utils/request";

export const fetchData = () => {
	return request({
		url: "./table.json",
		method: "get",
	});
};

// 规范数据类型
interface LoginInfo {
	username: string;
	password: string;
	grant_type: string;
	scope: string;
	client_id: string;
	client_secret: string;
}

export const login = (data: LoginInfo) => {
	let grant_type = data.grant_type;
	let username = data.username;
	let password = data.password;
	let scope = data.scope;
	let client_id = data.client_id;
	let client_secret = data.client_secret;
	return request({
		url: "proxy/apis/v1/login",
		method: "post",
		data:
			"grant_type=" +
			grant_type +
			"&username=" +
			username +
			"&password=" +
			password +
			"&scope=" +
			scope +
			"&client_id=" +
			client_id +
			"&client_secret=" +
			client_secret,
	});
};

export const fetchExcellentBarData = () => {
	return request({
		url: "proxy/apis/v1/excellentInfoBar",
		method: "get",
	});
};

export const fetchExcellentLineData = () => {
	return request({
		url: "proxy/apis/v1/excellentInfoLine",
		method: "get",
	});
};

export const fetchCoursesData = (term: String) => {
	return request({
		url: "proxy/apis/v1/scores/courses",
		method: "post",
		data: {
			term: term,
		},
	});
};

// 通过课程名下载该课程不及格名单-excel表格
export const downloadCoursesData = (data: Object) => {
	return request({
		url: "proxy/apis/v1/scores/courses/download",
		method: "post",
		data: data,
		responseType: "arraybuffer",
	});
};

export const downloadCourseFile = (grade: string) => {
	return request({
		url: "proxy/apis/v1/download/course",
		method: "post",
		data: {grade: grade},
		responseType: "arraybuffer",
	})
}

export const downloadStudentInfoFile = (data: object) => {
	return request({
		url: "proxy/apis/v1/studentInfo/download",
		method: "post",
		data: data,
		responseType: "arraybuffer",
	})
}

export const downloadStudentInfoFileDetail = (data: object) => {
	return request({
		url: "proxy/apis/v1/studentInfo/downloadDetail",
		method: "post",
		data: data,
		responseType: "arraybuffer",
	})
}

export const downloadGradeStudentFile = (data: object) => {
	return request({
		url: "proxy/apis/v1/grade/download",
		method: "post",
		data: data,
		responseType: "arraybuffer",
	})
}

export const courseCalculate = () => {
	return request({
		url: "proxy/apis/v1/courseCalculate",
		method: "get"
	})
}

export const scoreCalculate = () => {
	return request({
		url: "proxy/apis/v1/scoreCalculate",
		method: "get"
	})
}

export const fetchGradesData = (term: String) => {
	return request({
		url: "proxy/apis/v1/scores/grade",
		method: "post",
		data: {
			term: term,
		},
	});
};

export const fetchClassesData = (term: String) => {
	return request({
		url: "proxy/apis/v1/scores/class/chart",
		method: "post",
		data: {
			term: term,
		},
	});
};

export const fetchMajorData = () => {
	return request({
		url: "proxy/apis/v1/scores/major/chart",
		method: "get",
	});
};

export const fetchScoreData = (term: String) => {
	return request({
		url: "proxy/apis/v1/scores/score/chart",
		method: "post",
		data: {
			term: term,
		},
	});
};

export const fetchStudentInfoData = (grade: String) => {
	return request({
		url: "proxy/apis/v1/studentInfo/grade",
		method: "post",
		data: {
			"grade": grade,
		}
	});
};

export const fetchStudentInfoConfig = (grade: String) => {
	return request({
		url: "proxy/apis/v1/studentInfo/config",
		method: "post",
		data: {
			"grade": grade,
		}
	});
};

export const setStudentInfoConfig = (data: object) => {
	return request({
		url: "proxy/apis/v1/studentInfo/setConfig",
		method: "post",
		data: data
	});
}

export const fetchStudentClassData = () => {
	return request({
		url: "proxy/apis/v1/stuclasses",
		method: "get",
	});
};

export const fetchAnalysisData = (term: String, classesName: String) => {
	return request({
		url: "proxy/apis/v1/students/analysis",
		method: "post",
		data: {
			stuTermBar: term,
			stuClassID: classesName,
		},
	});
};

export const fetchUsersData = () => {
	return request({
		url: "proxy/apis/v1/users",
		method: "get",
	});
};

interface userInfo {
	cID: string;
	cName: string;
	is_active: boolean;
	is_superuser: boolean;
	password: string;
}
export const addUserData = (data: userInfo) => {
	return request({
		url: "proxy/apis/v1/users",
		method: "post",
		data,
	});
};

export const uploadFile = (data: FormData) => {
	return request({
		url: "proxy/apis/v1/uploadFile",
		method: "post",
		data: data,
		headers: {
			"Access-Control-Allow-Origin": "*",
			"Content-Type": "multipart/form-data",
		},
	});
};

export const uploadCourseFile = (data: FormData) => {
	return request({
		url: "proxy/apis/v1/uploadCourseFile",
		method: "post",
		data: data,
		headers: {
			"Access-Control-Allow-Origin": "*",
			"Content-Type": "multipart/form-data",
		},
	});
};

// 数据整理
export const dataReduction = () => {
	return request({
		url: "proxy/apis/v1/xlsxsqls",
		method: "get",
	});
};

export const dataReductionPersonal = () => {
	return request({
		url: "proxy/apis/v1/xlsxsqlspersonal",
		method: "get",
	});
};

export const fetchEachGradeNumber = () => {
	return request({
		url: "proxy/apis/v1/studentInfo/number",
		method: "get",
	});
};

export const uploadExcellentClassData = (data: Object) => {
    return request({
        url: "proxy/apis/v1/excellent/info",
        method: "post",
        data: data
    })
}

export const flushALLExcellent = () => {
	return request({
		url: "proxy/apis/v1/excellent/flushALL",
		method: "get",
	})
}

export const clearCalculateData = () => {
	return request({
		url: "proxy/apis/v1/file/clearCalculateData",
		method: "get",
	})
}

export const flushALLDatabase = () => {
	return request({
		url: "proxy/apis/v1/file/flushData",
		method: "get",
	})
}