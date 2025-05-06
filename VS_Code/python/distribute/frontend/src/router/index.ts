import {createRouter, createWebHashHistory, RouteRecordRaw} from "vue-router";
import { usePermissStore } from '../store/permiss'
import Home from "../views/home.vue";

const routes:RouteRecordRaw[] = [
    {
        path: '/',
        redirect: '/dashboard'
    }, {
        path: "/",
        name: "Home",
        component: Home,
        children: [
            {
                path: "/dashboard",
                name: "dashboard",
                meta: {
                    title: '系统首页',
                    permiss: '1'
                },
                component: () => import ( /* webpackChunkName: "dashboard" */ "../views/dashboard.vue")
            }, {
                path: "/table",
                name: "basetable",
                meta: {
                    title: '表格',
                    permiss: '2'
                },
                component: () => import ( /* webpackChunkName: "table" */ "../views/table.vue")
            }, {
                path: "/usersManagement",
                name: "usersManagement",
                meta: {
                    title: '用户管理',
                    permiss: '11'
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/usersManagement.vue")
            }, {
                path: "/passwordModify",
                name: "passwordModify",
                meta: {
                    title: '修改密码',
                    permiss: '11'
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/passwordModify.vue")
            }, {
                path: "/excellent",
                name: "excellent",
                meta: {
                    title: '优良学风班情况',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/excellent.vue")
            }, {
                path: "/courseDimension",
                name: "courseDimension",
                meta: {
                    title: '课程维度',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/courseDimension.vue")
            }, {
                path: "/gradesDimension",
                name: "gradesDimension",
                meta: {
                    title: '年级维度',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/gradesDimension.vue")
            },{
                path: "/classesDimension",
                name: "classesDimension",
                meta: {
                    title: '班级维度',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/classesDimension.vue")
            },{
                path: "/majorDimension",
                name: "majorDimension",
                meta: {
                    title: '专业维度',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/majorDimension.vue")
            },{
                path: "/scoreDimension",
                name: "scoreDimension",
                meta: {
                    title: '分数维度',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/scoreDimension.vue")
            }, {
                path: "/filesUpload",
                name: "filesUpload",
                meta: {
                    title: '文件上传',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/upload.vue")
            }, {
                path: "/studentInformation",
                name: "studentInformation",
                meta: {
                    title: '学生信息',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/studentInformation.vue")
            }, {
                path: "/studentInformationS",
                name: "studentInformationS",
                meta: {
                    title: '学生信息(精简)',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/studentInformation_simple.vue")
            },{
                path: "/failureAnalysis",
                name: "failureAnalysis",
                meta: {
                    title: '不及格分析',
                    permiss: '11',
                    keepAlive: true,
                },
                component: () => import ( /* webpackChunkName: "charts" */ "../views/failureAnalysis.vue")
            },{
                path: "/form",
                name: "baseform",
                meta: {
                    title: '表单',
                    permiss: '5'
                },
                component: () => import ( /* webpackChunkName: "form" */ "../views/form.vue")
            }, {
                path: "/tabs",
                name: "tabs",
                meta: {
                    title: 'tab标签',
                    permiss: '3'
                },
                component: () => import ( /* webpackChunkName: "tabs" */ "../views/tabs.vue")
            }, {
                path: "/donate",
                name: "donate",
                meta: {
                    title: '鼓励作者',
                    permiss: '14'
                },
                component: () => import ( /* webpackChunkName: "donate" */ "../views/donate.vue")
            }, {
                path: "/permission",
                name: "permission",
                meta: {
                    title: '权限管理',
                    permiss: '13'
                },
                component: () => import ( /* webpackChunkName: "permission" */ "../views/permission.vue")
            }, {
                path: "/upload",
                name: "upload",
                meta: {
                    title: '上传插件',
                    permiss: '6'
                },
                component: () => import ( /* webpackChunkName: "upload" */ "../views/upload.vue")
            }, {
                path: "/icon",
                name: "icon",
                meta: {
                    title: '自定义图标',
                    permiss: '10'
                },
                component: () => import ( /* webpackChunkName: "icon" */ "../views/icon.vue")
            },  {
                path: '/user',
                name: 'user',
                meta: {
                    title: '个人中心'
                },
                component: () => import (/* webpackChunkName: "user" */ '../views/user.vue')
            }, {
                path: '/editor',
                name: 'editor',
                meta: {
                    title: '富文本编辑器',
                    permiss: '8'
                },
                component: () => import (/* webpackChunkName: "editor" */ '../views/editor.vue')
            }, {
                path: '/markdown',
                name: 'markdown',
                meta: {
                    title: 'markdown编辑器',
                    permiss: '9'
                },
                component: () => import (/* webpackChunkName: "markdown" */ '../views/markdown.vue')
            }
        ]
    }, {
        path: "/login",
        name: "Login",
        meta: {
            title: '登录'
        },
        component: () => import ( /* webpackChunkName: "login" */ "../views/login.vue")
    }, {
        path: '/403',
        name: '403',
        meta: {
            title: '没有权限'
        },
        component: () => import (/* webpackChunkName: "403" */ '../views/403.vue')
    },
];

const router = createRouter({
    history: createWebHashHistory(),
    routes
});

router.beforeEach((to, from, next) => {
    document.title = `${to.meta.title} | vue-manage-system`;
    const role = localStorage.getItem('ms_username');
    const permiss = usePermissStore();
    if (!role && to.path !== '/login') {
        next('/login');
    } else if (to.meta.permiss && !permiss.key.includes(to.meta.permiss)) {
        // 如果没有权限，则进入403
        next('/403');
    } else {
        next();
    }
});

export default router;