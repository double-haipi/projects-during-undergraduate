/*
 *3d audio spectrum viauslizer built with three.js
 * revision 0.2.7
 *Mar 20,2014 Wayou
 *Licensed under the MIT license
 * view on github:https://github.com/Wayou/3D_Audio_Spectrum_VIsualizer/
 */
 


var Visualizer = function() {
    //this.appName='HTML5 3D Audio Spectrum Visualizer';
	this.appName='Do you  like it...';
    this.audioContext;
	
    this.source;
    //this.url = 'sources/bbc_sherlock_london.mp3';//需修改的地方***********************
	/*改成了数组，播放多首歌曲*/
	this.url=['sources/Take Me to Your Heart - Michael Learns To Rock.mp3','sources/YeKongZhongZuiLiangDeXing- Escape plan bank.mp3','sources/Summertrain - Greyson Chance.mp3','sources/JinShengJinShi - ManWenJun.mp3','sources/Marry You - Bruno Mars.mp3','sources/FengYuWuZu -ZhouHuaJian.mp3'];
	this.urlName=['Take Me to Your Heart - Michael Learns To Rock','YeKongZhongZuiLiangDeXing- Escape plan bank','Summertrain - Greyson Chance','JinShengJinShi - ManWenJun','Marry You - Bruno Mars','FengYuWuZu -ZhouHuaJian'];
	this.next=-1;
	this.lyrVisuable=0;
	this.file;
    this.infoContainer = document.getElementById('info');
    this.statsContainer = document.getElementById('stats');
    this.stats;
    this.gui;
    this.controls;
    this.status = 0; //flag to indicate the audio is palying or stoed
    this.processing = false; //detect if there's a file is under processing, if so refuse to handle new files
    this.forceStop = false; //the audio is stoped by a new file or normally end
    
	this.MWIDTH = 2;//柱宽
    this.GAP = 1;//柱间距
    this.METERNUM = Math.round(70 / (this.MWIDTH + this.GAP));  // calculated by 200/(MWIDTH+GAP),200 is the width of the visualizer area  柱条数量
    this.MTHICKNESS = 1;
    
	this.scene;
    this.render;
    this.camera;
    
	this.orbitControls;
    this.clock;
    
    this.animationId;
}
Visualizer.prototype = {
    init: function() { //prepare the audio and the scene
        //fix the browser vendor
        window.requestAnimationFrame = window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame;
        window.cancelAnimationFrame = window.cancelAnimationFrame || window.webkitCancelAnimationFrame || window.mozCancelAnimationFrame;
        window.AudioContext = window.AudioContext || window.webkitAudioContext || window.mozAudioContext;
        try {
            this.audioContext = new AudioContext();
			
        } catch (e) {
            this.infoContainer.textContent = 'audio context is not supported :(';
        }
		
        this._handleDragDrop();//
        this._initStats();//
        this._initControlPanel();//
        this._prepareScene();//
        this._initControls();//
    },
	//显示FPS，包含在初始化中***** 
    _initStats: function(statsContainer) {
        var stats = new Stats();
        stats.domElement.style.position = 'absolute';
        stats.domElement.style.right = '-100px'; //default left and top is 0px, so actually there's no need to set it
        stats.domElement.style.bottom = '-100px';//简单的对其隐藏
        this.statsContainer.appendChild(stats.domElement);
        this.stats = stats;
    },
	//控制面板*****
    _initControlPanel: function() {
        var controlPanel = document.getElementById('controlPanel'),
            actionBtn = document.getElementById('action');
        actionBtn.onclick = function() {
            var top = controlPanel.style.top;
            if (top == '0px' || top == '') {
                controlPanel.style.top = '-190px';
                actionBtn.textContent = 'Show';
            } else {
                controlPanel.style.top = '0px';
                actionBtn.textContent = 'Hide';
            };
        };
    },
	//控制初始化*****
    _initControls: function() {
        var gui = this.gui,
            controls = this.controls,
            orbitControls = this.orbitControls,
            scene = this.scene;
        gui = new dat.GUI(); //the control panel
		//定义控件
        controls = new function() {
            this.capColor = 0xFFFFFF;
            this.barColor = 0x01FF00;
            this.ambientColor = 0x0c0c0c;
            this.dropSpeed = 0.1;
            this.autoRotate = false;
			//this.autoRotate = true;
        };
        //initialize the control ui, custom the meter color
        gui.add(controls, 'dropSpeed', 0.1, 0.5);// 下降速度范围
		//改变cap 颜色
        gui.addColor(controls, 'capColor').onChange(function(e) {
            scene.children.forEach(function(child) {
                if (child.name.indexOf('cap') > -1) {
                    child.material.color.setStyle(e);
                    child.material.ambient = new THREE.Color(e)
                    child.material.emissive = new THREE.Color(e)
                    child.material.needsUpdate = true;
                }
            });
        });
        gui.addColor(controls, 'barColor').onChange(function(e) {
            scene.children.forEach(function(child) {
                if (child.name.indexOf('cube') > -1) {
                    child.material.color.setStyle(e);
                    child.material.ambient = new THREE.Color(e)
                    child.material.emissive = new THREE.Color(e)
                    child.material.needsUpdate = true;
                }
            });
        });
        gui.add(controls, 'autoRotate').onChange(function(e) {
            orbitControls.autoRotate = e;
        });
        // gui.addColor(controls, 'meterBottomColor').onChange(function(e) {
        //     // cube.color = new THREE.Color(e);
        // });
        this.controls = controls;
        this.gui = gui;
    },
	//文件获取的三种方法：通过文件类型的input来进行文件选择，监听input的onchnage事件；通过拖拽的形式把文件拖放到页面进行获取；新开一个Ajax异步请求来获取文件*****
    _handleDragDrop: function() {
		this.lyrVisuable=0;
        var that = this,
           // dropContainer = document.body,
			dropContainer =document.getElementsByTagName("body")[0],
            uploadBtn = document.getElementById('upload');
        //listen the file upload
        uploadBtn.onchange = function() {
            if (!that.audioContext || that.processing) {
                return;
            };
            if (uploadBtn.files.length !== 0) {
                that.processing = true;
                that.infoContainer.textContent = 'uploading...';
                that.file = uploadBtn.files[0];
                that.fileName = that.file.name;
                that._readFile(that.file);//读取函数
                uploadBtn.value='';//fix for chrome: when uploading the same file this onchange event wont trigger
            };
        };
        //handle drag and drop
        dropContainer.addEventListener("dragenter", function() {
            if (that.processing) {
                return;
            };
            that.infoContainer.textContent = 'drop it to the page...';
        }, false);
        dropContainer.addEventListener("dragover", function(e) {
            e.stopPropagation();
            e.preventDefault();
            e.dataTransfer.dropEffect = 'copy';//文件放置类型为拷贝
        }, false);
        dropContainer.addEventListener("dragleave", function() {
            if (that.status) {
                that.infoContainer.textContent = 'playing ' + that.fileName;
            } else {
                that.infoContainer.textContent = that.appName;
            };
        }, false);
		//注意：上下两个监听事件理解的时候顺序调换一下，执行是不受影响的
        dropContainer.addEventListener("drop", function(e) {
            e.stopPropagation();
            e.preventDefault();
            if (!that.audioContext || that.processing) {
                console.log('there is a file under processing, please wait');//控制台输出日志
                return;
            };
            that.processing = true;
            that.infoContainer.textContent = 'uploading...';
            //get the dropped file
            that.file = e.dataTransfer.files[0];
            that.fileName = that.file.name;
            that._readFile(e.dataTransfer.files[0]);
        }, false);
    },
	//下一曲按钮
	nextSong:function() {
		if(this.next>=this.url.length-1)
		this.next=0;
		else
		this.next++;
		this.loadDefaultAndPlay(this.url[this.next]);
	
		},
	/*	
   //控制歌词显示  使用此种方法未实现
   comeOn:function()//开始播放
    { 
	
	offsetTime= this.audioContext.currentTime;
	mPlay();
	//window.setInterval(this.comeOn(),1000);
    this.comeOn();
	 },*/
		
	//Visualizer的函数（方法）
    loadDefaultAndPlay: function(url) {
		this.lyrVisuable=1;
        var that = this,
            // load the default file
            xhr = new XMLHttpRequest();//新开一个请求
        if (!this.audioContext) {
            this.processing = false;
            this.infoContainer.textContent = 'audio context is not supported :(';
            return;
        };
        if (this.processing) {
            this.processing = false;
            console.log('there is a file under processing, please wait');
            return;
        };
		//可能需修改*****
       // this.fileName = 'bbc_sherlock_london.mp3'
		this.fileName = this.urlName[this.next];
        xhr.open('GET', url, true);//配置好请求类型，文件路径等
        xhr.responseType = "arraybuffer"; //配置数据返回类型
        xhr.onload = function() {
            that.infoContainer.textContent = 'load success, start next process...';
            var result = xhr.response;
            that.play(result);//
        };
        xhr.onerror = xhr.onabord = function() {
            that.processing = false;
            that.infoContainer.textContent = 'fail to load the audio :(';
        };
        this.infoContainer.textContent = 'loading the audio...';
        this.processing = true;
        xhr.send();
    },
    _readFile: function(file) {
		this.lyrVisuable=0;
        var that = this,
            fr = new FileReader();
        fr.onload = function(e) {
            var fileResult = e.target.result;
            if (!that.audioContext) {
                return;
            };
            that.play(fileResult);
        };
        fr.onerror = function(e) {
            this.processing = false;
            that.infoContainer.textContent = '!Fail to read';
        };
        that.infoContainer.textContent = 'Starting read the file';
        fr.readAsArrayBuffer(file);
    },
	//
    play: function(audio) {
        var that = this;
        that.infoContainer.textContent = 'Decoding the audio...';
        this.audioContext.decodeAudioData(audio, function(buffer) {
            that.infoContainer.textContent = 'Decode succussfully,start the visualizer';
            that._visualize(buffer);
        }, function(e) {
            that.processing = false;
            that.infoContainer.textContent = '!Fail to decode';
        });
    },
    _visualize: function(buffer) {
        var audioContext = this.audioContext,
            audioBufferSouceNode = audioContext.createBufferSource(),
            analyser = audioContext.createAnalyser(),
            that = this;
        //connect the source to the analyser
        audioBufferSouceNode.connect(analyser);
        //connect the analyser to the destination(the speaker), or we won't hear the sound
        analyser.connect(audioContext.destination);
        //then assign the buffer to the buffer source node
        audioBufferSouceNode.buffer = buffer;
        //stop the previous sound if any
        if (this.source) {
            if (this.status != 0) {
                this.forceStop = true;
                this.source.stop(0);//停止方法************
            };
        }
        this.source = audioBufferSouceNode;
        audioBufferSouceNode.start(0);//开始计时
		
		//歌词是否显示   不同的加载方式给予其一个标志值，标志值不同执行不同方案
		if(this.lyrVisuable!=0)
		{comeOn(this.next);}//开始播放时获取显示的歌词  这个过程所费时间基本可以不计 
		else{comeOn(songLy.length-1);} //
		
		
		this.status = 1;
        this.processing = false;
        this.source.onended = function() {
            that._audioEnd();
        };
        this.infoContainer.textContent = this.fileName;
        if (this.animationId) {
            cancelAnimationFrame(this.animationId);
        };
        this._drawVisualizer(this.scene, this.render, this.camera, analyser);
    },
    _audioEnd: function() {
        if (this.forceStop) {
            this.forceStop = false;
            return;
        } else {
            this.forceStop = false;
            this.status = 0;
            this.infoContainer.textContent = this.appName;
        };
    },
    _prepareScene: function() {
        var that = this,
            WIDTH = window.innerWidth,
            HEIGHT = window.innerHeight,
            GAP = this.GAP, //distance between 2 meters
            MWIDTH = this.MWIDTH, //width of the meter
            METERNUM = this.METERNUM, //how many meter will be in the spectrum visualizer
            MTHICKNESS = this.MTHICKNESS, //the thickness of the meter
            stats = this.stats, //display fps info for webgl render
            controls = this.controls,
            gui = this.gui,
            axes = new THREE.AxisHelper(20), //the axes for debug using
            scene = new THREE.Scene(),
            render = new THREE.WebGLRenderer({
                antialias: true
            }),
            camera = new THREE.PerspectiveCamera(45, WIDTH / HEIGHT, 0.1, 1000),
            plane,
            planeGeometry,
            planeMaterial,
            spotLight = new THREE.SpotLight(0xffffff),
            ambientLight = new THREE.AmbientLight(0x0c0c0c),
            //make the camera movable
            orbitControls = new THREE.OrbitControls(camera);
        orbitControls.minDistance = 70;//限制相机的z轴范围
        orbitControls.maxDistance = 200;
        orbitControls.maxPolarAngle = 2;//限制相机转过的角度（绕x轴）1.57
		//orbitControls.maxPolarAngle = 2;//限制相机转过的角度（绕x轴）
        orbitControls.noPan = true;
		//orbitControls.noPan = false;
		 orbitControls.noRotate=true;/*因为歌词面板原因，禁用旋转*/
        clock = new THREE.Clock();
        //add the axes for debug
        //scene.add(axes); 
        //the render
        render.setClearColor(0x212121);
        render.setSize(WIDTH, HEIGHT);
        render.shadowMapEnabled = true;
        //the plane
        planeGeometry = new THREE.PlaneGeometry(200, 200);
        // planeMaterial = new THREE.MeshLambertMaterial({
        //     color: 0xcccccc
        // });
        planeMaterial = new THREE.MeshPhongMaterial({
            color: 0x222222,
            ambient: 0x555555,
            specular: 0xdddddd,
            shininess: 5,
            reflectivity: 2
        });
        planeMaterial.side = THREE.DoubleSide;
        plane = new THREE.Mesh(planeGeometry, planeMaterial);
        plane.rotation.x = -0.5 * Math.PI;
        plane.position.x = 0;
		//plane.position.y = 0;
        plane.position.y = -35;//下移平面
        plane.position.z = 0;
        plane.receiveShadow = true;
        scene.add(plane);
        //the cube    *************************************************
        var cubeGeometry = new THREE.CubeGeometry(MWIDTH, 1, MTHICKNESS);
        // var cubeMaterial = new THREE.MeshLambertMaterial({
        //     color: 0x01FF00
        // });
        var cubeMaterial = new THREE.MeshPhongMaterial({
            color: 0x01FF00,
            ambient: 0x01FF00,
            specular: 0x01FF00,
            shininess: 20,
            reflectivity: 5.5
        });
        var capGeometry = new THREE.CubeGeometry(MWIDTH, 0.5, MTHICKNESS);
        var capMaterial = new THREE.MeshPhongMaterial({
            color: 0xffffff,
            ambient: 0x01FF00,
            specular: 0x01FF00,
            shininess: 20,
            reflectivity: 5.5
        });
        for (var i = METERNUM - 1; i >= 0; i--) {
            // var cubeMaterial = new THREE.MeshPhongMaterial({
            //     color: Math.random()*0xffffff,
            //     ambient: 0x808080,
            //     specular: 0xffffff,
            //     shininess: 20,
            //     reflectivity: 5.5
            // });
            var cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
            cube.position.x = -35 + (MWIDTH + GAP) * i;
            //cube.position.y = -1;
			cube.position.y = -36;
            cube.position.z = 0.5;
            cube.castShadow = true;
            cube.name = 'cube' + i;
            scene.add(cube);
            var cap = new THREE.Mesh(capGeometry, capMaterial);
            cap.position.x = -35 + (MWIDTH + GAP) * i;
            cap.position.y = -34.5;
            cap.position.z = 0.5;
            cap.castShadow = true;
            cap.name = 'cap' + i;
            scene.add(cap);
        };
        //the camera***************************************************
        camera.position.x = 50;
        camera.position.y = 40;
        camera.position.z = 86.6;
        camera.lookAt(scene.position);
        //add an ambient light for a better look
        scene.add(ambientLight);
        //the spot light
        spotLight.position.set(0, 60, 40);
        //spotLight.castShadow = true;
        scene.add(spotLight);
        var directionalLight = new THREE.DirectionalLight(0xffffff, 0.7);
        directionalLight.castShadow = true;
        directionalLight.position.set(0, 10, 10);
        scene.add(directionalLight);
        //output the scene to the page
        document.getElementById('visualizer_container').appendChild(render.domElement);
        render.render(scene, camera);
        this.scene = scene;
        this.render = render;
        this.camera = camera;
        this.orbitControls = orbitControls;
        this.clock = clock;
        this.orbitControls = orbitControls;
        this._drawVisualizer(scene, render, camera);
    },
    _drawVisualizer: function(scene, render, camera, analyser) {
        var that = this,
            WIDTH = window.innerWidth,
            HEIGHT = window.innerHeight,
            GAP = this.GAP, //distance between 2 meters
            MWIDTH = this.MWIDTH, //width of the meter
            METERNUM = this.METERNUM, //how many meter will be in the spectrum visualizer
            MTHICKNESS = this.MTHICKNESS, //the thickness of the meter
            stats = this.stats, //display fps info for webgl render
            controls = this.controls,
            gui = this.gui,
            clock = this.clock,
            orbitControls = this.orbitControls;
        var renderAnimation = function() {
            that.stats.update();
            var delta = clock.getDelta();
            orbitControls.update(delta);
            if (analyser) {
                //get spectrum data from the analyser
                var array = new Uint8Array(analyser.frequencyBinCount);
                analyser.getByteFrequencyData(array);
                //update the height of each meter
                var step = Math.round(array.length / METERNUM);/* //sample limited data from the total array*/
                for (var i = 0; i < METERNUM; i++) {
                    var value = array[i * step] / 4;
                    value = value < 1 ? 1 : value; //NOTE: if the scale value is less than 1 there will be warnings in the console! so lets make sure its above 1
                    var meter = scene.getObjectByName('cube' + i, true),
                        cap = scene.getObjectByName('cap' + i, true);
                    meter.scale.y = value;
                    //meter.scale.set(1, value < 1 ? 1 : value, 1);//another way to scale
                    //ref1:http://stackoverflow.com/questions/12924883/three-js-webgl-scale-to-fixed-dimensions
                    //ref1:http://stackoverflow.com/questions/15492857/any-way-to-get-a-bounding-box-from-a-three-js-object3d
                    meter.geometry.computeBoundingBox();//计算包围盒大小从而获得物体尺寸，计算的是原来的不是缩放后的
                    height = (meter.geometry.boundingBox.max.y - meter.geometry.boundingBox.min.y) * value;
                   /* if (height / 2 > cap.position.y) {
                        cap.position.y = (height / 2-0.5)>0?(height / 2-36):-34.5;
                    } else {
                        cap.position.y -= controls.dropSpeed;
                    };*/
					 if (cap.position.y-(height / 2-36) <=1) {
                        cap.position.y = (height / 2-0.5)>0?(height / 2-36+1):-34.5;
                    } else {
                        cap.position.y -= controls.dropSpeed;
                    };
                }
            };
            //render all stuff out
            render.render(scene, camera);
            that.animationId = requestAnimationFrame(renderAnimation);
        };
        that.animationId = requestAnimationFrame(renderAnimation);
    }
}




