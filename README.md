# OpenGL-Hpp: C++ Bindings for OpenGL

The goal of the OpenGL-Hpp is to provide header only C++ bindings for the OpenGL C API to improve the developers OpenGL experience without introducing CPU runtime cost. It adds features like type safety for enums and bitfields, STL container support, exceptions and simple enumerations.
This Project is get inspiration from Vulkan-Hpp, and use some source code of it.Thank for every contributor to Vulkan-Hpp !


## Getting Started
Just `#include <gl.hpp>` and you're ready to use the C++ bindings.

### Minimum Requirements

OpenGL-Hpp requires a C++17 capable compiler to compile.

The OpenGL version must be 4.5 or higher.

I will add support to without DSA in a long term.

## Usage

### namespace gl

To avoid name collisions with the OpenGL C API the C++ bindings reside in the gl namespace. The following rules apply to the new naming.
Also add some generic supprt
  * `glCreateBuffers(N, ...)` can be accessed as `gl::createObject<Buffer,N>(...)`
  or `gl::createObjectv<Buffer>(N, ...)`

  * the `gl::createObject` will return a `Buffer` variable if `N` be `1`, else it will return `std::array<Buffer,N>` variable

  * the `gl::createObjectv` will return `std::vector<Buffe>` variable,this version is designed for run-time length variable 

* Enums are mapped to scoped enums to provide compile time type safety. The names have been changed to 'e' + CamelCase with the GL_ prefix and type infix removed. In case the enum type is an extension the extension suffix has been removed from the enum values.

In all other cases the extension suffix has not been removed.
  * `GL_INVALID_OPERATION` is now `gl::Error::eInvalidOperation`.
  * the *`pname`* of *`glGet*`* such as `GL_ELEMENT_ARRAY_BUFFER_BINDING` is now map to `gl::StateVariables::eElementArrayBufferBinding`.
  * the *`target`* parameter of *`glBindBuffer`* such as`GL_ARRAY_BUFFER` is now `gl::Buffer::BindTarget::eArrayBuffer`.
  * the *`target`* parameter of *`glBindBuffer(Base/Range)`* such as `GL_ATOMIC_COUNTER_BUFFER` is now `gl::Buffer::BindBaseTarget::eAtomicCounterBuffer` to avoid invaild enum error

In some cases it might be necessary to move OpenGL-Hpp to a custom namespace. This can be achieved by defining OPENGL_HPP_NAMESPACE before including OpenGL-Hpp.

### Handles

OpenGL-Hpp declares a class for all handles to ensure full type safety and to add support for member functions on handles. A member function has been added to a handle class for each function which accepts the corresponding handle as first parameter. Instead of `glVertexArrayAttribBinding(`*`vaobj`*`, ...)` one can write `vaobj.attribBinding(...)`.

### C/C++ Interop for Handles

it is recommended to use a `static_cast` for the conversion like this: `GLuint vaoHandle = static_cast<GLuint>(cppVertexArray)` to prevent converting some arbitrary int to a handle or vice versa by accident.

<!-- ### Flags

The scoped enum feature adds type safety to the flags, but also prevents using the flag bits as input for bitwise operations like & and |.

As solution Vulkan-Hpp provides a template class `vk::Flags` which brings the standard operations like `&=`, `|=`, `&` and `|` to our scoped enums. Except for the initialization with 0 this class behaves exactly like a normal bitmask with the improvement that it is impossible to set bits not specified by the corresponding enum by accident. Here are a few examples for the bitmask handling:

```c++
vk::ImageUsageFlags iu1; // initialize a bitmask with no bit set
vk::ImageUsageFlags iu2 = {}; // initialize a bitmask with no bit set
vk::ImageUsageFlags iu3 = vk::ImageUsageFlagBits::eColorAttachment; // initialize with a single value
vk::ImageUsageFlags iu4 = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eStorage; // or two bits to get a bitmask
PipelineShaderStageCreateInfo ci( {} /* pass a flag without any bits set */, ...);
```

### CreateInfo structs

When constructing a handle in Vulkan one usually has to create some `CreateInfo` struct which describes the new handle. This can result in quite lengthy code as can be seen in the following Vulkan C example:

```c++
VkImageCreateInfo ci;
ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
ci.pNext = nullptr;
ci.flags = ...some flags...;
ci.imageType = VK_IMAGE_TYPE_2D;
ci.format = VK_FORMAT_R8G8B8A8_UNORM;
ci.extent = VkExtent3D { width, height, 1 };
ci.mipLevels = 1;
ci.arrayLayers = 1;
ci.samples = VK_SAMPLE_COUNT_1_BIT;
ci.tiling = VK_IMAGE_TILING_OPTIMAL;
ci.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
ci.queueFamilyIndexCount = 0;
ci.pQueueFamilyIndices = 0;
ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
vkCreateImage(device, &ci, allocator, &image));
```

There are two typical issues Vulkan developers encounter when filling out a CreateInfo struct field by field
* One or more fields are left uninitialized.
* `sType` is incorrect.

Especially the first one is hard to detect.

Vulkan-Hpp provides constructors for all CreateInfo objects which accept one parameter for each member variable. This way the compiler throws a compiler error if a value has been forgotten. In addition to this `sType` is automatically filled with the correct value and `pNext` set to a `nullptr` by default. Here's how the same code looks with a constructor:

```c++
vk::ImageCreateInfo ci({}, vk::ImageType::e2D, vk::Format::eR8G8B8A8Unorm,
                       { width, height, 1 },
                       1, 1, vk::SampleCountFlagBits::e1,
                       vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eColorAttachment,
                       vk::SharingMode::eExclusive, 0, nullptr, vk::ImageLayout::eUndefined);
vk::Image image = device.createImage(ci);
```

With constructors for CreateInfo structures one can also pass temporaries to Vulkan functions like this:

```c++
vk::Image image = device.createImage({{}, vk::ImageType::e2D, vk::Format::eR8G8B8A8Unorm,
                                     { width, height, 1 },
                                     1, 1, vk::SampleCountFlagBits::e1,
                                     vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eColorAttachment,
                                     vk::SharingMode::eExclusive, 0, nullptr, vk::ImageLayout::eUndefined});
```

### Designated Initializers

Beginning with C++20, C++ supports designated initializers. As that feature requires to not have any user-declared or inherited constructors, you have to `#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS`, which removes all the structure constructors from vulkan.hpp. Instead you can then use aggregate initialization. The first few vk-lines in your source might then look like
```c++
// initialize the vk::ApplicationInfo structure
vk::ApplicationInfo applicationInfo{ .pApplicationName   = AppName,
                                     .applicationVersion = 1,
                                     .pEngineName        = EngineName,
                                     .engineVersion      = 1,
                                     .apiVersion         = VK_API_VERSION_1_1 };
        
// initialize the vk::InstanceCreateInfo
vk::InstanceCreateInfo instanceCreateInfo{ .pApplicationInfo = & applicationInfo };
```
instead of
```c++
// initialize the vk::ApplicationInfo structure
vk::ApplicationInfo applicationInfo( AppName, 1, EngineName, 1, VK_API_VERSION_1_1 );
        
// initialize the vk::InstanceCreateInfo
vk::InstanceCreateInfo instanceCreateInfo( {}, &applicationInfo );
```
Note, that the designator order needs to match the declaration order.
Note as well, that now you can explicitly set the sType member of vk-structures. This is neither neccessary (as they are correctly initialized by default) nor recommended. -->

### Passing Arrays to Functions using ArrayProxy 
### (this facility source code is from Vulkan-Hpp)

you can use it to simple pass array to Function,such as `gl::deleteObject<Buffer>(buffers)` rather than `glDeleteBuffers(size,&buffers[0])`

there is introduction of ArrayProxy in Vulkan-Hpp

The Vulkan API has several places where which require (count,pointer) as two function arguments and C++ has a few containers which map perfectly to this pair. To simplify development the Vulkan-Hpp bindings have replaced those argument pairs with the `ArrayProxy` template class which accepts empty arrays and a single value as well as STL containers `std::initializer_list`, `std::array` and `std::vector` as argument for construction. This way a single generated Vulkan version can accept a variety of inputs without having the combinatoric explosion which would occur when creating a function for each container type.

Here are some code samples on how to use the ArrayProxy:

```c++
vk::CommandBuffer c;

// pass an empty array
c.setScissor(0, nullptr);

// pass a single value. Value is passed as reference
vk::Rect2D scissorRect = { {0, 0}, {640, 480} };
c.setScissor(0, scissorRect);

// pass a temporary value.
c.setScissor(0, { { 0, 0 },{ 640, 480 } });

// generate a std::initializer_list using two rectangles from the stack. This might generate a copy of the rectangles.
vk::Rect2D scissorRect1 = { { 0, 0 },{ 320, 240 } };
vk::Rect2D scissorRect2 = { { 320, 240 },{ 320, 240 } };
c.setScissor(0, { scissorRect, scissorRect2 });

// construct a std::initializer_list using two temporary rectangles.
c.setScissor(0, { { {   0,   0 },{ 320, 240 } },
                { { 320, 240 },{ 320, 240 } }
}
);

// pass a std::array
std::array<vk::Rect2D, 2> arr{ scissorRect1, scissorRect2 };
c.setScissor(0, arr);

// pass a std::vector of dynamic size
std::vector<vk::Rect2D> vec;
vec.push_back(scissorRect1);
vec.push_back(scissorRect2);
c.setScissor(0, vec);
```

<!-- ### Passing Structs to Functions

Vulkan-Hpp generates references for pointers to structs. This conversion allows passing temporary structs to functions which can result in shorter code. In case the input is optional and thus accepting a null pointer the parameter type will be a `vk::Optional<T> const&` type. This type accepts either a reference to `T` or nullptr as input and thus allows optional temporary structs.

```c++
// C
VkImageSubresource subResource;
subResource.aspectMask = 0;
subResource.mipLevel = 0;
subResource.arrayLayer = 0;
VkSubresourceLayout layout;
vkGetImageSubresourceLayout(device, image, &subresource, &layout);

// C++
auto layout = device.getImageSubresourceLayout(image, { {} /* flags*/, 0 /* miplevel */, 0 /* arrayLayer */ });
```

### Structure Pointer Chains

Vulkan allows chaining of structures through the pNext pointer. Vulkan-Hpp has a variadic template class which allows constructing of such structure chains with minimal efforts. In addition to this it checks at compile time if the spec allows the construction of such a `pNext` chain.

```c++
// This will compile successfully.
vk::StructureChain<vk::MemoryAllocateInfo, vk::ImportMemoryFdInfoKHR> c;
vk::MemoryAllocateInfo &allocInfo = c.get<vk::MemoryAllocateInfo>();
vk::ImportMemoryFdInfoKHR &fdInfo = c.get<vk::ImportMemoryFdInfoKHR>();

// This will fail compilation since it's not valid according to the spec.
vk::StructureChain<vk::MemoryAllocateInfo, vk::MemoryDedicatedRequirementsKHR> c;
vk::MemoryAllocateInfo &allocInfo = c.get<vk::MemoryAllocateInfo>();
vk::ImportMemoryFdInfoKHR &fdInfo = c.get<vk::ImportMemoryFdInfoKHR>();
```

Vulkan-Hpp provides a constructor for these chains similar to the CreateInfo objects which accepts a list of all structures part of the chain. The `pNext` field is automatically set to the correct value:

```c++
vk::StructureChain<vk::MemoryAllocateInfo, vk::MemoryDedicatedAllocateInfo> c = {
  vk::MemoryAllocateInfo(size, type),
  vk::MemoryDedicatedAllocateInfo(image)
};
```

If one of the structures of a StructureChain is to be removed, maybe due to some optional settings, you can use the function ```vk::StructureChain::unlink<ClassType>()```. It modifies the StructureChain such that the specified structure isn't part of the pNext-chain any more. Note, that the actual memory layout of the StructureChain is not modified by that function.
In case that very same structure has to be re-added to the StructureChain again, use ```vk::StructureChain::relink<ClassType>()```.

Sometimes the user has to pass a preallocated structure chain to query information. For those cases there are two corresponding getter functions. One with a variadic template generating a structure chain of at least two elements to construct the return value:

```c++
// Query vk::MemoryRequirements2HR and vk::MemoryDedicatedRequirementsKHR when calling Device::getBufferMemoryRequirements2KHR:
auto result = device.getBufferMemoryRequirements2KHR<vk::MemoryRequirements2KHR, vk::MemoryDedicatedRequirementsKHR>({});
vk::MemoryRequirements2KHR &memReqs = result.get<vk::MemoryRequirements2KHR>();
vk::MemoryDedicatedRequirementsKHR &dedMemReqs = result.get<vk::MemoryDedicatedRequirementsKHR>();
```

To get just the base structure, without chaining, the other getter function provided does not need a template argument for the structure to get:

```
// Query just vk::MemoryRequirements2KHR
vk::MemoryRequirements2KHR memoryRequirements = device.getBufferMemoryRequirements2KHR({});
```

### Return values, Error Codes & Exceptions

By default Vulkan-Hpp has exceptions enabled. This means that Vulkan-Hpp checks the return code of each function call which returns a Vk::Result. If Vk::Result is a failure a std::runtime_error will be thrown. Since there is no need to return the error code anymore the C++ bindings can now return the actual desired return value, i.e. a vulkan handle. In those cases ResultValue <SomeType>::type is defined as the returned type.

To create a device you can now just write:

```C++
vk::Device device = physicalDevice.createDevice(createInfo);
```

Some functions allow more than just `vk::Result::eSuccess` to be considered as a success code. For those functions, we always return a `ResultValue<SomeType>`. An example is `acquireNextImage2KHR`, that can be used like this:

```C++
vk::ResultValue<uint32_t> result = device->acquireNextImage2KHR(acquireNextImageInfo);
switch (result.result)
{
	case vk::Result::eSuccess:
		currentBuffer = result.value;
		break;
	case vk::Result::eTimeout:
	case vk::Result::eNotReady:
	case vk::Result::eSuboptimalKHR:
		// do something meaningfull
		break;
	default:
		// should not happen, as other return codes are considered to be an error and throw an exception
		break;
}
```

As time passes, some vulkan functions might change, such that they start to support more result codes than `vk::Result::eSuccess` as a success code. That logical change would not be visible in the C-API, but in the C++-API, as such a function would now return a `vk::ResultValue<SomeType>` instead of just `SomeType`. In such (rare) cases, you would have to adjust your cpp-sources to reflect that API change.

If exception handling is disabled by defining `VULKAN_HPP_NO_EXCEPTIONS` the type of `ResultValue<SomeType>::type` is a struct holding a `vk::Result` and a `SomeType`. This struct supports unpacking the return values by using `std::tie`.

In case you don’t want to use the `vk::ArrayProxy` and return value transformation you can still call the plain C-style function. Below are three examples showing the 3 ways to use the API:

The first snippet shows how to use the API without exceptions and the return value transformation:

```c++
// No exceptions, no return value transformation
ShaderModuleCreateInfo createInfo(...);
ShaderModule shader1;
Result result = device.createShaderModule(&createInfo, allocator, &shader1);
if (result.result != VK_SUCCESS)
{
    handle error code;
    cleanup?
    return?
}

ShaderModule shader2;
Result result = device.createShaderModule(&createInfo, allocator, &shader2);
if (result != VK_SUCCESS)
{
    handle error code;
    cleanup?
    return?
}
```

The second snippet shows how to use the API using return value transformation, but without exceptions. It’s already a little bit shorter than the original code:

```c++
ResultValue<ShaderModule> shaderResult1 = device.createShaderModule({...} /* createInfo temporary */);
if (shaderResult1.result != VK_SUCCESS)
{
  handle error code;
  cleanup?
  return?
}

// std::tie support.
vk::Result result;
vk::ShaderModule shaderModule2;
std::tie(result, shaderModule2)  = device.createShaderModule({...} /* createInfo temporary */);
if (shaderResult2.result != VK_SUCCESS)
{
  handle error code;
  cleanup?
  return?
}
```

A nicer way to unpack the result is provided by the structured bindings of C++17. They will allow us to get the result with a single line of code:

```c++
auto [result, shaderModule2] = device.createShaderModule({...} /* createInfo temporary */);
```

Finally, the last code example is using exceptions and return value transformation. This is the default mode of the API.

```c++
 ShaderModule shader1;
 ShaderModule shader2;
 try {
   shader1 = device.createShaderModule({...});
   shader2 = device.createShaderModule({...});
 } catch(std::exception const &e) {
   // handle error and free resources
 }
```

Keep in mind that Vulkan-Hpp does not support RAII style handles and that you have to cleanup your resources in the error handler!

### C++17: [[nodiscard]]

With C++17 and above, some functions are attributed with [[nodiscard]], resulting in a warning if you don't use the return value in any way. You can switch those warnings off by defining VULKAN_HPP_NO_NODISCARD_WARNINGS.

### Enumerations

For the return value transformation, there's one special class of return values which require special handling: Enumerations. For enumerations you usually have to write code like this:

```c++
std::vector<LayerProperties,Allocator> properties;
uint32_t propertyCount;
Result result;
do
{
  // determine number of elements to query
  result = static_cast<Result>( vk::enumerateDeviceLayerProperties( m_physicalDevice, &propertyCount, nullptr ) );
  if ( ( result == Result::eSuccess ) && propertyCount )
  {
    // allocate memory & query again
    properties.resize( propertyCount );
    result = static_cast<Result>( vk::enumerateDeviceLayerProperties( m_physicalDevice, &propertyCount, reinterpret_cast
     <VkLayerProperties*>( properties.data() ) ) );
  }
} while ( result == Result::eIncomplete );
// it's possible that the count has changed, start again if properties was not big enough
properties.resize(propertyCount);
```

Since writing this loop over and over again is tedious and error prone the C++ binding takes care of the enumeration so that you can just write:

```c++
std::vector<LayerProperties> properties = physicalDevice.enumerateDeviceLayerProperties();
```

### UniqueHandle for automatic resource management

Vulkan-Hpp provides a `vk::UniqueHandle<Type, Deleter>` interface. For each Vulkan handle type `vk::Type` there is a unique handle `vk::UniqueType` which will delete the underlying Vulkan resource upon destruction, e.g. `vk::UniqueBuffer ` is the unique handle for `vk::Buffer`.

For each function which constructs a Vulkan handle of type `vk::Type` Vulkan-Hpp provides a second version which returns a `vk::UniqueType`. E.g. for `vk::Device::createBuffer` there is `vk::Device::createBufferUnique` and for `vk::allocateCommandBuffers` there is `vk::allocateCommandBuffersUnique`.

Note that using `vk::UniqueHandle` comes at a cost since most deleters have to store the `vk::AllocationCallbacks` and parent handle used for construction because they are required for automatic destruction.

### Custom allocators

Sometimes it is required to use `std::vector` with custom allocators. Vulkan-Hpp supports vectors with custom allocators as input for `vk::ArrayProxy` and for functions which do return a vector. For the latter case, add your favorite custom allocator as template argument to the function call like this:

```c++
std::vector<LayerProperties, MyCustomAllocator> properties = physicalDevice.enumerateDeviceLayerProperties<MyCustomAllocator>();
```

You can as well use a stateful custom allocator by providing it as an argument to those functions. Unfortunately, to make the compilers happy, you also need to explicitly set the Dispatch argument. To get the default there, a simple ´´´{}´´´ would suffice:

```c++
MyStatefulCustomAllocator allocator;
std::vector<LayerProperties, MyStatefulCustomAllocator> properties = physicalDevice.enumerateDeviceLayerProperties( allocator, {} );
```


### Custom assertions

All over vulkan.hpp, there are a couple of calls to an assert function. By defining `VULKAN_HPP_ASSERT`, you can specifiy your own custom assert function to be called instead.

By default, `VULKAN_HPP_ASSERT_ON_RESULT` will be used for checking results when `VULKAN_HPP_NO_EXCEPTIONS` is defined. If you want to handle errors by yourself, you can disable/customize it just like `VULKAN_HPP_ASSERT`. -->

### Extensions / Per Device function pointers

this is a very similar facility with Vulkan-Hpp，you can use it without link library or extra source file such as glad，this feature is enable default，

To use the ```DispatchLoaderDynamic``` as the default dispatcher (means: you don't need to explicitly add it to every function call),  you need to  have the macro ```OPENGL_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE``` excactly once in your source code to provide storage for that default dispatcher. Then you should call `gl::initLoader(...)` with the function (function pointer or lambda and so on) which have a from `void* (const char*)`

For all functions, that OPENGL_HPP_DEFAULT_DISPATCHER is the default for the last argument to that function. In case you want to explicitly provide the dispatcher for each and every function call (when you have multiple dispatchers for different devices, for example) and you want to make sure, that you don't accidentally miss any function call

```c++

#include <GLFW/glfw3.h>
...
#include <gl.hpp>

// give the dispatch loader storage youself
OPENGL_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

int main(){
    // init GLFW
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("can not init GLFW !");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    
    if (!(window = glfwCreateWindow(800, 800, "test", nullptr, nullptr))) {
        throw std::runtime_error("can not create window !");
    }

    glfwMakeContextCurrent(window);

    // init dynamic dispatch loader with one call
    gl::initLoader(glfwGetProcAddress);

    // can use raw OpenGL call in such form, you can also define a short alias
    std::cout << OPENGL_HPP_DEFAULT_DISPATCHER.glGetString(GL_VERSION)
                  << std::endl;

    auto vaos = gl::createObjectv<gl::Buffer>(2);
}
```


## License

The ArrayProxy source is copy from Vulkan-Hpp Project,and several facilitis is get inspired by that Project.

Copyright 2015-2020 The Khronos Group Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
