/*
** Copyright 2018 Bloomberg Finance L.P.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/
//NOTE: DO NOT INCLUDE DIRECTLY

//##############################################################################################
//#################################### IMPLEMENTATIONS #########################################
//##############################################################################################

namespace Bloomberg {
namespace quantum {

template <class T>
Buffer<T>::Buffer() :
    _isClosed(false)
{}

template <class T>
template <class V>
BufferStatus Buffer<T>::push(V&& value)
{
    if (_isClosed)
    {
        return BufferStatus::Closed;
    }
    _buffer.push_back(std::forward<V>(value));
    return BufferStatus::DataPosted;
}

template <class T>
BufferStatus Buffer<T>::pull(T& value)
{
    if (_buffer.empty())
    {
        return _isClosed ? BufferStatus::Closed : BufferStatus::DataPending;
    }
    value = std::move(_buffer.front());
    _buffer.pop_front();
    return BufferStatus::DataReceived;
}

template <class T>
void Buffer<T>::close()
{
    _isClosed = true;
}

template <class T>
size_t Buffer<T>::size()
{
    return _buffer.size();
}

template <class T>
bool Buffer<T>::empty()
{
    return _buffer.empty();
}

}}
