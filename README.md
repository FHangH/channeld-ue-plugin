# ChanneldUE Plugin

The open source plugin that enables distributed simulation with Unreal Engine's dedicated servers. 

ChanneldUE是为虚幻引擎专用服务器提供分布式模拟能力的开源插件。

## Features
- Increase the maximum capacity of a single UE dedicated server to 100-200 players without modifying the engine code.
- Can combine multiple dedicated servers into one large world, supporting thousands of players online concurrently.
- Support a variety of application scenarios, including seamless large worlds, as well as traditional multi-room architecture and relay server architecture.
- Out-of-the-box synchronization solution that seamlessly integrates with the native UE's networking framework.
- Agile and extensible client interest management mechanism.
- Support cross-server interaction (currently only support cross-server RPC, Character Movement, and Rigidbody Physics; cross-server for AI, GAS and other systems requires additional integration).
- Dedicated server disaster recovery without client disconnection/restart.
- Cloud-based dynamic load balancing can greatly save server costs (under development).
- Support one-click cloud deployment.

## 特性
- 无需修改引擎代码，便可将单个UE专用服务器的最大承载人数提升到100-200人
- 可以将多个UE专用服务器组合成一个大世界，支持上千玩家同时在线
- 支持多种应用场景，包括无缝大世界，以及传统的多房间架构和中转服务器架构
- 开箱即用的同步方案，与原生UE的开发方式无缝集成
- 灵活且可扩展的客户端兴趣管理机制
- 支持跨服交互（目前仅支持RPC、角色移动、刚体物理跨服；AI、GAS等系统的跨服需要额外集成）
- 在客户端不需要重连或重新开始的情况下进行专用服务器灾难恢复
- 基于云计算的动态负载均衡能够极大节省服务器成本（开发中）
- 支持一键上云

## Links
[Getting Started](https://www.channeld.org/#/installation)

[Documentation](https://www.channeld.org/#/?id=channeldue-plugin)

[ChanneldUE Example Project](https://github.com/channeldorg/channeld-ue-demos)

[Code repo of channeld, the Gateway Service behind ChanneldUE](https://github.com/channeldorg/channeld)

## 链接
[快速开始](https://www.channeld.org/#/zh/installation)

[中文文档](https://www.channeld.org/#/zh/)

[ChanneldUE示例项目](https://github.com/channeldorg/channeld-ue-demos)

[channeld网关服务代码仓库](https://github.com/channeldorg/channeld)

## Engine Versions Support Matrix
| Components | UE 4.27.2 | UE 5.2.1 | UE 5.3.2 |
| ------ | ------ | ------ |------ |
| Getting Started | :white_check_mark: | :white_check_mark: | :white_check_mark: |
| Demos Project | :white_check_mark: | :white_check_mark: | :white_check_mark: |
| Codegen Tool | :white_check_mark: | :white_check_mark: `*` | :white_check_mark: `*` |
| Cloud Deployment Tool | :white_check_mark: | :x: | :x:

`*` Need to turn off `Live Coding` in order to hot-reload the generated code.
## 引擎版本支持
| 覆盖功能 | UE 4.27.2 | UE 5.2.1 | UE 5.3.2 |
| ------ | ------ | ------ |------ |
| 快速开始文档 | :white_check_mark: | :white_check_mark: | :white_check_mark: |
| 示例项目 | :white_check_mark: | :white_check_mark: | :white_check_mark: |
| 代码生成工具 | :white_check_mark: | :white_check_mark: `*` | :white_check_mark: `*` |
| 云部署工具 | :white_check_mark: | :x: | :x:

`*` 需要关闭`实施代码编写`功能才能正常热加载生成的代码。

## License and Disclaimer
- ChanneldUE plugin is licensed under the Apache 2.0 license, see [LICENSE](LICENSE) for details.
- ChanneldUE plugin and channeld gateway service are free to use for any purpose, including commercial use.
- The user is responsible for all risks when using this plugin and channeld gateway service.
- Basic technical support is provided in the form of GitHub [Issues](/../../issues) and [Discussions](/../../discussions), but do not guarantee to solve all problems in time.
- For further inquiry, please contact: [indiestian@gmail.com](mailto:indiestian@gmail.com)

## 使用许可和免责声明
- ChanneldUE插件使用Apache 2.0许可证，详情请参考[LICENSE](LICENSE)文件。
- ChanneldUE插件及channeld网关服务的代码供所有人免费使用，可以用于任何目的，包括商业用途（欢迎白嫖，更欢迎提交反馈和PR）。
- 使用本插件及channeld网关服务时，应自行承担所有风险。
- 您可以通过GitHub [Issues](/../../issues)和[Discussions](/../../discussions)的形式获取基本的技术支持，但不保证能够及时解决所有问题。
- 联系开发者：
  - [indiestian@gmail.com](mailto:indiestian@gmail.com)
  - QQ群：664754097
